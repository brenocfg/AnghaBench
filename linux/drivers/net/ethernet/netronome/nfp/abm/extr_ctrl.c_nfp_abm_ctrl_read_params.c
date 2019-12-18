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
struct nfp_abm_link {TYPE_1__* vnic; int /*<<< orphan*/  queue_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  stride_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_START_RXQ ; 
 int nfp_abm_ctrl_prio_check_params (struct nfp_abm_link*) ; 
 int /*<<< orphan*/  nn_readl (TYPE_1__*,int /*<<< orphan*/ ) ; 

int nfp_abm_ctrl_read_params(struct nfp_abm_link *alink)
{
	alink->queue_base = nn_readl(alink->vnic, NFP_NET_CFG_START_RXQ);
	alink->queue_base /= alink->vnic->stride_rx;

	return nfp_abm_ctrl_prio_check_params(alink);
}