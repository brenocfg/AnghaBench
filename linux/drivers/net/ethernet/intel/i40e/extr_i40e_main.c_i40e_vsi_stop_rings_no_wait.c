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
struct i40e_vsi {int base_queue; int num_queue_pairs; struct i40e_pf* back; } ;
struct i40e_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_control_rx_q (struct i40e_pf*,int,int) ; 
 int /*<<< orphan*/  i40e_control_tx_q (struct i40e_pf*,int,int) ; 

void i40e_vsi_stop_rings_no_wait(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;
	int i, pf_q;

	pf_q = vsi->base_queue;
	for (i = 0; i < vsi->num_queue_pairs; i++, pf_q++) {
		i40e_control_tx_q(pf, pf_q, false);
		i40e_control_rx_q(pf, pf_q, false);
	}
}