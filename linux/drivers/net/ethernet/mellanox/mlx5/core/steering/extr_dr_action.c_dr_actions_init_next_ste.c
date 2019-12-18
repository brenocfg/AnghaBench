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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlx5dr_ste_entry_type { ____Placeholder_mlx5dr_ste_entry_type } mlx5dr_ste_entry_type ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SIZE ; 
 int /*<<< orphan*/  MLX5DR_STE_LU_TYPE_DONT_CARE ; 
 int /*<<< orphan*/  mlx5dr_ste_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dr_actions_init_next_ste(u8 **last_ste,
				     u32 *added_stes,
				     enum mlx5dr_ste_entry_type entry_type,
				     u16 gvmi)
{
	(*added_stes)++;
	*last_ste += DR_STE_SIZE;
	mlx5dr_ste_init(*last_ste, MLX5DR_STE_LU_TYPE_DONT_CARE, entry_type, gvmi);
}