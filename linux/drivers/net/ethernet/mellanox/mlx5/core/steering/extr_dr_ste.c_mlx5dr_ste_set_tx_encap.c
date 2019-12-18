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
typedef  int u32 ;

/* Variables and functions */
 int DR_STE_ACTION_TYPE_ENCAP ; 
 int DR_STE_ACTION_TYPE_ENCAP_L3 ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  action_description ; 
 int /*<<< orphan*/  action_type ; 
 int /*<<< orphan*/  encap_pointer_vlan_data ; 
 int /*<<< orphan*/  ste_sx_transmit ; 

void mlx5dr_ste_set_tx_encap(void *hw_ste_p, u32 reformat_id, int size, bool encap_l3)
{
	MLX5_SET(ste_sx_transmit, hw_ste_p, action_type,
		 encap_l3 ? DR_STE_ACTION_TYPE_ENCAP_L3 : DR_STE_ACTION_TYPE_ENCAP);
	/* The hardware expects here size in words (2 byte) */
	MLX5_SET(ste_sx_transmit, hw_ste_p, action_description, size / 2);
	MLX5_SET(ste_sx_transmit, hw_ste_p, encap_pointer_vlan_data, reformat_id);
}