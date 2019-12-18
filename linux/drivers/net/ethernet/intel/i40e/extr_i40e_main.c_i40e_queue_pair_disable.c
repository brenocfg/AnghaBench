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
struct i40e_vsi {int dummy; } ;

/* Variables and functions */
 int i40e_enter_busy_conf (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_queue_pair_clean_rings (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_queue_pair_disable_irq (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_queue_pair_reset_stats (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_queue_pair_toggle_napi (struct i40e_vsi*,int,int) ; 
 int i40e_queue_pair_toggle_rings (struct i40e_vsi*,int,int) ; 

int i40e_queue_pair_disable(struct i40e_vsi *vsi, int queue_pair)
{
	int err;

	err = i40e_enter_busy_conf(vsi);
	if (err)
		return err;

	i40e_queue_pair_disable_irq(vsi, queue_pair);
	err = i40e_queue_pair_toggle_rings(vsi, queue_pair, false /* off */);
	i40e_queue_pair_toggle_napi(vsi, queue_pair, false /* off */);
	i40e_queue_pair_clean_rings(vsi, queue_pair);
	i40e_queue_pair_reset_stats(vsi, queue_pair);

	return err;
}