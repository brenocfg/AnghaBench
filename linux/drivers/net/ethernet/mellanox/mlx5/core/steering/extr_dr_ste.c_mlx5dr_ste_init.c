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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5DR_STE_LU_TYPE_DONT_CARE ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry_sub_type ; 
 int /*<<< orphan*/  miss_address_63_48 ; 
 int /*<<< orphan*/  next_lu_type ; 
 int /*<<< orphan*/  next_table_base_63_48 ; 
 int /*<<< orphan*/  ste_general ; 
 int /*<<< orphan*/  ste_rx_steering_mult ; 

void mlx5dr_ste_init(u8 *hw_ste_p, u8 lu_type, u8 entry_type,
		     u16 gvmi)
{
	MLX5_SET(ste_general, hw_ste_p, entry_type, entry_type);
	MLX5_SET(ste_general, hw_ste_p, entry_sub_type, lu_type);
	MLX5_SET(ste_general, hw_ste_p, next_lu_type, MLX5DR_STE_LU_TYPE_DONT_CARE);

	/* Set GVMI once, this is the same for RX/TX
	 * bits 63_48 of next table base / miss address encode the next GVMI
	 */
	MLX5_SET(ste_rx_steering_mult, hw_ste_p, gvmi, gvmi);
	MLX5_SET(ste_rx_steering_mult, hw_ste_p, next_table_base_63_48, gvmi);
	MLX5_SET(ste_rx_steering_mult, hw_ste_p, miss_address_63_48, gvmi);
}