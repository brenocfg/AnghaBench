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
struct i40e_vsi {int base_queue; int num_queue_pairs; int alloc_queue_pairs; int /*<<< orphan*/  seid; struct i40e_pf* back; } ;
struct i40e_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int i40e_pf_rxq_wait (struct i40e_pf*,int,int) ; 
 int i40e_pf_txq_wait (struct i40e_pf*,int,int) ; 

int i40e_vsi_wait_queues_disabled(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;
	int i, pf_q, ret;

	pf_q = vsi->base_queue;
	for (i = 0; i < vsi->num_queue_pairs; i++, pf_q++) {
		/* Check and wait for the Tx queue */
		ret = i40e_pf_txq_wait(pf, pf_q, false);
		if (ret) {
			dev_info(&pf->pdev->dev,
				 "VSI seid %d Tx ring %d disable timeout\n",
				 vsi->seid, pf_q);
			return ret;
		}

		if (!i40e_enabled_xdp_vsi(vsi))
			goto wait_rx;

		/* Check and wait for the XDP Tx queue */
		ret = i40e_pf_txq_wait(pf, pf_q + vsi->alloc_queue_pairs,
				       false);
		if (ret) {
			dev_info(&pf->pdev->dev,
				 "VSI seid %d XDP Tx ring %d disable timeout\n",
				 vsi->seid, pf_q);
			return ret;
		}
wait_rx:
		/* Check and wait for the Rx queue */
		ret = i40e_pf_rxq_wait(pf, pf_q, false);
		if (ret) {
			dev_info(&pf->pdev->dev,
				 "VSI seid %d Rx ring %d disable timeout\n",
				 vsi->seid, pf_q);
			return ret;
		}
	}

	return 0;
}