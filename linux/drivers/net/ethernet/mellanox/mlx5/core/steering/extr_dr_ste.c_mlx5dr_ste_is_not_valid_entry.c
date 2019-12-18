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
struct dr_hw_ste_format {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5DR_STE_LU_TYPE_NOP ; 
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,struct dr_hw_ste_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_lu_type ; 
 int /*<<< orphan*/  ste_general ; 

bool mlx5dr_ste_is_not_valid_entry(u8 *p_hw_ste)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)p_hw_ste;

	if (MLX5_GET(ste_general, hw_ste, next_lu_type) ==
	    MLX5DR_STE_LU_TYPE_NOP)
		return true;

	return false;
}