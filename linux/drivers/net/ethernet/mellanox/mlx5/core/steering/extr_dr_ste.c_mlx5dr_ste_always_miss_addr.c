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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5dr_ste {int /*<<< orphan*/ * hw_ste; } ;
struct dr_hw_ste_format {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5DR_STE_LU_TYPE_DONT_CARE ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_ste_set_always_miss (struct dr_hw_ste_format*) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_miss_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_lu_type ; 
 int /*<<< orphan*/  ste_rx_steering_mult ; 

void mlx5dr_ste_always_miss_addr(struct mlx5dr_ste *ste, u64 miss_addr)
{
	u8 *hw_ste = ste->hw_ste;

	MLX5_SET(ste_rx_steering_mult, hw_ste, next_lu_type, MLX5DR_STE_LU_TYPE_DONT_CARE);
	mlx5dr_ste_set_miss_addr(hw_ste, miss_addr);
	dr_ste_set_always_miss((struct dr_hw_ste_format *)ste->hw_ste);
}