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
struct reset_controller_dev {scalar_t__ of_reset_n_cells; int nr_resets; } ;
struct of_phandle_args {scalar_t__ args_count; scalar_t__* args; } ;
struct mmp_clk_reset_unit {struct mmp_clk_reset_cell* cells; } ;
struct mmp_clk_reset_cell {scalar_t__ clk_id; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 struct mmp_clk_reset_unit* rcdev_to_unit (struct reset_controller_dev*) ; 

__attribute__((used)) static int mmp_of_reset_xlate(struct reset_controller_dev *rcdev,
			  const struct of_phandle_args *reset_spec)
{
	struct mmp_clk_reset_unit *unit = rcdev_to_unit(rcdev);
	struct mmp_clk_reset_cell *cell;
	int i;

	if (WARN_ON(reset_spec->args_count != rcdev->of_reset_n_cells))
		return -EINVAL;

	for (i = 0; i < rcdev->nr_resets; i++) {
		cell = &unit->cells[i];
		if (cell->clk_id == reset_spec->args[0])
			break;
	}

	if (i == rcdev->nr_resets)
		return -EINVAL;

	return i;
}