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
struct TYPE_4__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  class; int /*<<< orphan*/  resv; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_rx_rings; int /*<<< orphan*/  num_tx_rings; scalar_t__ is_vf; } ;
struct nfp_net {int cap; int /*<<< orphan*/  app; int /*<<< orphan*/  max_mtu; TYPE_2__ fw_ver; int /*<<< orphan*/  max_rx_rings; TYPE_1__ dp; int /*<<< orphan*/  max_tx_rings; } ;

/* Variables and functions */
 int NFP_NET_CFG_CTRL_CSUM_COMPLETE ; 
 int NFP_NET_CFG_CTRL_CTAG_FILTER ; 
 int NFP_NET_CFG_CTRL_GATHER ; 
 int NFP_NET_CFG_CTRL_IRQMOD ; 
 int NFP_NET_CFG_CTRL_L2BC ; 
 int NFP_NET_CFG_CTRL_L2MC ; 
 int NFP_NET_CFG_CTRL_LIVE_ADDR ; 
 int NFP_NET_CFG_CTRL_LSO ; 
 int NFP_NET_CFG_CTRL_LSO2 ; 
 int NFP_NET_CFG_CTRL_MSIXAUTO ; 
 int NFP_NET_CFG_CTRL_NVGRE ; 
 int NFP_NET_CFG_CTRL_PROMISC ; 
 int NFP_NET_CFG_CTRL_RSS ; 
 int NFP_NET_CFG_CTRL_RSS2 ; 
 int NFP_NET_CFG_CTRL_RXCSUM ; 
 int NFP_NET_CFG_CTRL_RXVLAN ; 
 int NFP_NET_CFG_CTRL_SCATTER ; 
 int NFP_NET_CFG_CTRL_TXCSUM ; 
 int NFP_NET_CFG_CTRL_TXVLAN ; 
 int NFP_NET_CFG_CTRL_VXLAN ; 
 int /*<<< orphan*/  nfp_app_extra_cap (int /*<<< orphan*/ ,struct nfp_net*) ; 
 int /*<<< orphan*/  nn_info (struct nfp_net*,char*,...) ; 

void nfp_net_info(struct nfp_net *nn)
{
	nn_info(nn, "Netronome NFP-6xxx %sNetdev: TxQs=%d/%d RxQs=%d/%d\n",
		nn->dp.is_vf ? "VF " : "",
		nn->dp.num_tx_rings, nn->max_tx_rings,
		nn->dp.num_rx_rings, nn->max_rx_rings);
	nn_info(nn, "VER: %d.%d.%d.%d, Maximum supported MTU: %d\n",
		nn->fw_ver.resv, nn->fw_ver.class,
		nn->fw_ver.major, nn->fw_ver.minor,
		nn->max_mtu);
	nn_info(nn, "CAP: %#x %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		nn->cap,
		nn->cap & NFP_NET_CFG_CTRL_PROMISC  ? "PROMISC "  : "",
		nn->cap & NFP_NET_CFG_CTRL_L2BC     ? "L2BCFILT " : "",
		nn->cap & NFP_NET_CFG_CTRL_L2MC     ? "L2MCFILT " : "",
		nn->cap & NFP_NET_CFG_CTRL_RXCSUM   ? "RXCSUM "   : "",
		nn->cap & NFP_NET_CFG_CTRL_TXCSUM   ? "TXCSUM "   : "",
		nn->cap & NFP_NET_CFG_CTRL_RXVLAN   ? "RXVLAN "   : "",
		nn->cap & NFP_NET_CFG_CTRL_TXVLAN   ? "TXVLAN "   : "",
		nn->cap & NFP_NET_CFG_CTRL_SCATTER  ? "SCATTER "  : "",
		nn->cap & NFP_NET_CFG_CTRL_GATHER   ? "GATHER "   : "",
		nn->cap & NFP_NET_CFG_CTRL_LSO      ? "TSO1 "     : "",
		nn->cap & NFP_NET_CFG_CTRL_LSO2     ? "TSO2 "     : "",
		nn->cap & NFP_NET_CFG_CTRL_RSS      ? "RSS1 "     : "",
		nn->cap & NFP_NET_CFG_CTRL_RSS2     ? "RSS2 "     : "",
		nn->cap & NFP_NET_CFG_CTRL_CTAG_FILTER ? "CTAG_FILTER " : "",
		nn->cap & NFP_NET_CFG_CTRL_MSIXAUTO ? "AUTOMASK " : "",
		nn->cap & NFP_NET_CFG_CTRL_IRQMOD   ? "IRQMOD "   : "",
		nn->cap & NFP_NET_CFG_CTRL_VXLAN    ? "VXLAN "    : "",
		nn->cap & NFP_NET_CFG_CTRL_NVGRE    ? "NVGRE "	  : "",
		nn->cap & NFP_NET_CFG_CTRL_CSUM_COMPLETE ?
						      "RXCSUM_COMPLETE " : "",
		nn->cap & NFP_NET_CFG_CTRL_LIVE_ADDR ? "LIVE_ADDR " : "",
		nfp_app_extra_cap(nn->app, nn));
}