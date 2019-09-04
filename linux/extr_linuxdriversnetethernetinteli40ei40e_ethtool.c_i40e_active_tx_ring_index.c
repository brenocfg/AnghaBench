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
typedef  scalar_t__ u16 ;
struct i40e_vsi {scalar_t__ num_queue_pairs; scalar_t__ alloc_queue_pairs; } ;

/* Variables and functions */
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 

__attribute__((used)) static bool i40e_active_tx_ring_index(struct i40e_vsi *vsi, u16 index)
{
	if (i40e_enabled_xdp_vsi(vsi)) {
		return index < vsi->num_queue_pairs ||
			(index >= vsi->alloc_queue_pairs &&
			 index < vsi->alloc_queue_pairs + vsi->num_queue_pairs);
	}

	return index < vsi->num_queue_pairs;
}