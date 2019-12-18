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
struct TYPE_2__ {int ctrl; } ;
struct nfp_net {TYPE_1__ dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_CTRL ; 
 int NFP_NET_CFG_CTRL_BPF ; 
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE_GEN ; 
 int nfp_net_reconfig (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nfp_net_bpf_stop(struct nfp_net *nn)
{
	if (!(nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF))
		return 0;

	nn->dp.ctrl &= ~NFP_NET_CFG_CTRL_BPF;
	nn_writel(nn, NFP_NET_CFG_CTRL, nn->dp.ctrl);

	return nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_GEN);
}