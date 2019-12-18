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
struct i40e_vsi {int base_queue; int num_queue_pairs; int alloc_queue_pairs; int /*<<< orphan*/  seid; struct i40e_pf* back; } ;
struct i40e_pf {int dummy; } ;

/* Variables and functions */
 int i40e_control_wait_tx_q (int /*<<< orphan*/ ,struct i40e_pf*,int,int,int) ; 
 int /*<<< orphan*/  i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 

__attribute__((used)) static int i40e_vsi_control_tx(struct i40e_vsi *vsi, bool enable)
{
	struct i40e_pf *pf = vsi->back;
	int i, pf_q, ret = 0;

	pf_q = vsi->base_queue;
	for (i = 0; i < vsi->num_queue_pairs; i++, pf_q++) {
		ret = i40e_control_wait_tx_q(vsi->seid, pf,
					     pf_q,
					     false /*is xdp*/, enable);
		if (ret)
			break;

		if (!i40e_enabled_xdp_vsi(vsi))
			continue;

		ret = i40e_control_wait_tx_q(vsi->seid, pf,
					     pf_q + vsi->alloc_queue_pairs,
					     true /*is xdp*/, enable);
		if (ret)
			break;
	}
	return ret;
}