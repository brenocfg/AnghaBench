#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mtu; int ctrl; scalar_t__ netdev; int /*<<< orphan*/  fl_bufsz; int /*<<< orphan*/  rx_dma_dir; } ;
struct nfp_net {scalar_t__ max_mtu; int cap; TYPE_1__ dp; scalar_t__ tx_bar; scalar_t__ qcp_cfg; TYPE_2__* app; } ;
struct TYPE_4__ {scalar_t__ ctrl_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  NFP_NET_CFG_CTRL ; 
 int NFP_NET_CFG_CTRL_CMSG_DATA ; 
 int NFP_NET_CFG_CTRL_IRQMOD ; 
 int NFP_NET_CFG_CTRL_L2BC ; 
 int NFP_NET_CFG_CTRL_RSS ; 
 int NFP_NET_CFG_CTRL_RSS2 ; 
 int NFP_NET_CFG_CTRL_RSS_ANY ; 
 int /*<<< orphan*/  NFP_NET_CFG_RXRS_ENABLE ; 
 int /*<<< orphan*/  NFP_NET_CFG_TXRS_ENABLE ; 
 int NFP_NET_CFG_UPDATE_GEN ; 
 int NFP_NET_CFG_UPDATE_RING ; 
 scalar_t__ NFP_NET_DEFAULT_MTU ; 
 scalar_t__ NFP_QCP_QUEUE_ADDR_SZ ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ nfp_app_ctrl_uses_data_vnics (TYPE_2__*) ; 
 int /*<<< orphan*/  nfp_ccm_mbox_clean (struct nfp_net*) ; 
 int nfp_ccm_mbox_init (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_calc_fl_bufsz (TYPE_1__*) ; 
 int /*<<< orphan*/  nfp_net_irqmod_init (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_is_data_vnic (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_netdev_init (struct nfp_net*) ; 
 int nfp_net_read_caps (struct nfp_net*) ; 
 int nfp_net_reconfig (struct nfp_net*,int) ; 
 int /*<<< orphan*/  nfp_net_rss_init (struct nfp_net*) ; 
 int nfp_net_tls_init (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_vecs_init (struct nfp_net*) ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writeq (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (scalar_t__) ; 

int nfp_net_init(struct nfp_net *nn)
{
	int err;

	nn->dp.rx_dma_dir = DMA_FROM_DEVICE;

	err = nfp_net_read_caps(nn);
	if (err)
		return err;

	/* Set default MTU and Freelist buffer size */
	if (!nfp_net_is_data_vnic(nn) && nn->app->ctrl_mtu) {
		nn->dp.mtu = min(nn->app->ctrl_mtu, nn->max_mtu);
	} else if (nn->max_mtu < NFP_NET_DEFAULT_MTU) {
		nn->dp.mtu = nn->max_mtu;
	} else {
		nn->dp.mtu = NFP_NET_DEFAULT_MTU;
	}
	nn->dp.fl_bufsz = nfp_net_calc_fl_bufsz(&nn->dp);

	if (nfp_app_ctrl_uses_data_vnics(nn->app))
		nn->dp.ctrl |= nn->cap & NFP_NET_CFG_CTRL_CMSG_DATA;

	if (nn->cap & NFP_NET_CFG_CTRL_RSS_ANY) {
		nfp_net_rss_init(nn);
		nn->dp.ctrl |= nn->cap & NFP_NET_CFG_CTRL_RSS2 ?:
					 NFP_NET_CFG_CTRL_RSS;
	}

	/* Allow L2 Broadcast and Multicast through by default, if supported */
	if (nn->cap & NFP_NET_CFG_CTRL_L2BC)
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_L2BC;

	/* Allow IRQ moderation, if supported */
	if (nn->cap & NFP_NET_CFG_CTRL_IRQMOD) {
		nfp_net_irqmod_init(nn);
		nn->dp.ctrl |= NFP_NET_CFG_CTRL_IRQMOD;
	}

	/* Stash the re-configuration queue away.  First odd queue in TX Bar */
	nn->qcp_cfg = nn->tx_bar + NFP_QCP_QUEUE_ADDR_SZ;

	/* Make sure the FW knows the netdev is supposed to be disabled here */
	nn_writel(nn, NFP_NET_CFG_CTRL, 0);
	nn_writeq(nn, NFP_NET_CFG_TXRS_ENABLE, 0);
	nn_writeq(nn, NFP_NET_CFG_RXRS_ENABLE, 0);
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_RING |
				   NFP_NET_CFG_UPDATE_GEN);
	if (err)
		return err;

	if (nn->dp.netdev) {
		nfp_net_netdev_init(nn);

		err = nfp_ccm_mbox_init(nn);
		if (err)
			return err;

		err = nfp_net_tls_init(nn);
		if (err)
			goto err_clean_mbox;
	}

	nfp_net_vecs_init(nn);

	if (!nn->dp.netdev)
		return 0;
	return register_netdev(nn->dp.netdev);

err_clean_mbox:
	nfp_ccm_mbox_clean(nn);
	return err;
}