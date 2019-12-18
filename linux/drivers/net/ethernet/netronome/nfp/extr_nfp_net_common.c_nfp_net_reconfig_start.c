#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nfp_net {int /*<<< orphan*/  reconfig_in_progress_update; int /*<<< orphan*/  qcp_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE ; 
 int /*<<< orphan*/  nfp_qcp_wr_ptr_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_pci_flush (struct nfp_net*) ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_reconfig_start(struct nfp_net *nn, u32 update)
{
	nn_writel(nn, NFP_NET_CFG_UPDATE, update);
	/* ensure update is written before pinging HW */
	nn_pci_flush(nn);
	nfp_qcp_wr_ptr_add(nn->qcp_cfg, 1);
	nn->reconfig_in_progress_update = update;
}