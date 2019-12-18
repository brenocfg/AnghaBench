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
struct TYPE_4__ {int crypto_ops; int mbox_cmsg_types; int /*<<< orphan*/  crypto_enable_off; int /*<<< orphan*/  mbox_len; } ;
struct TYPE_3__ {struct net_device* netdev; } ;
struct nfp_net {TYPE_2__ tlv_caps; TYPE_1__ dp; } ;
struct nfp_crypto_req_add_v6 {int dummy; } ;
struct net_device {int /*<<< orphan*/ * tlsdev_ops; int /*<<< orphan*/  features; int /*<<< orphan*/  hw_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_HW_TLS_RX ; 
 int /*<<< orphan*/  NETIF_F_HW_TLS_TX ; 
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE_CRYPTO ; 
 int NFP_NET_TLS_CCM_MBOX_OPS_MASK ; 
 int NFP_NET_TLS_OPCODE_MASK ; 
 int NFP_NET_TLS_OPCODE_MASK_RX ; 
 int NFP_NET_TLS_OPCODE_MASK_TX ; 
 int __nfp_net_reconfig (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ccm_mbox_fits (struct nfp_net*,int) ; 
 int /*<<< orphan*/  nfp_net_tls_ops ; 
 int nfp_net_tls_reset (struct nfp_net*) ; 
 int /*<<< orphan*/  nn_ctrl_bar_lock (struct nfp_net*) ; 
 int /*<<< orphan*/  nn_ctrl_bar_unlock (struct nfp_net*) ; 
 int /*<<< orphan*/  nn_warn (struct nfp_net*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfp_net_tls_init(struct nfp_net *nn)
{
	struct net_device *netdev = nn->dp.netdev;
	int err;

	if (!(nn->tlv_caps.crypto_ops & NFP_NET_TLS_OPCODE_MASK))
		return 0;

	if ((nn->tlv_caps.mbox_cmsg_types & NFP_NET_TLS_CCM_MBOX_OPS_MASK) !=
	    NFP_NET_TLS_CCM_MBOX_OPS_MASK)
		return 0;

	if (!nfp_ccm_mbox_fits(nn, sizeof(struct nfp_crypto_req_add_v6))) {
		nn_warn(nn, "disabling TLS offload - mbox too small: %d\n",
			nn->tlv_caps.mbox_len);
		return 0;
	}

	err = nfp_net_tls_reset(nn);
	if (err)
		return err;

	nn_ctrl_bar_lock(nn);
	nn_writel(nn, nn->tlv_caps.crypto_enable_off, 0);
	err = __nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_CRYPTO);
	nn_ctrl_bar_unlock(nn);
	if (err)
		return err;

	if (nn->tlv_caps.crypto_ops & NFP_NET_TLS_OPCODE_MASK_RX) {
		netdev->hw_features |= NETIF_F_HW_TLS_RX;
		netdev->features |= NETIF_F_HW_TLS_RX;
	}
	if (nn->tlv_caps.crypto_ops & NFP_NET_TLS_OPCODE_MASK_TX) {
		netdev->hw_features |= NETIF_F_HW_TLS_TX;
		netdev->features |= NETIF_F_HW_TLS_TX;
	}

	netdev->tlsdev_ops = &nfp_net_tls_ops;

	return 0;
}