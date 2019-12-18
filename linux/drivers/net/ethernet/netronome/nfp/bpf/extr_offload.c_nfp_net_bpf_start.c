#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;
struct nfp_net {TYPE_1__ dp; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_CTRL ; 
 int /*<<< orphan*/  NFP_NET_CFG_CTRL_BPF ; 
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE_GEN ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int nfp_net_reconfig (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_net_bpf_start(struct nfp_net *nn, struct netlink_ext_ack *extack)
{
	int err;

	/* Enable passing packets through BPF function */
	nn->dp.ctrl |= NFP_NET_CFG_CTRL_BPF;
	nn_writel(nn, NFP_NET_CFG_CTRL, nn->dp.ctrl);
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_GEN);
	if (err)
		NL_SET_ERR_MSG_MOD(extack,
				   "FW command error while enabling BPF");
}