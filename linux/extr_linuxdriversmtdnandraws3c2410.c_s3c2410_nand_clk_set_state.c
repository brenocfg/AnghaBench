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
struct s3c2410_nand_info {scalar_t__ clk_state; int /*<<< orphan*/  clk; } ;
typedef  enum s3c_nand_clk_state { ____Placeholder_s3c_nand_clk_state } s3c_nand_clk_state ;

/* Variables and functions */
 scalar_t__ CLOCK_ENABLE ; 
 int CLOCK_SUSPEND ; 
 int /*<<< orphan*/  allow_clk_suspend (struct s3c2410_nand_info*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2410_nand_clk_set_state(struct s3c2410_nand_info *info,
		enum s3c_nand_clk_state new_state)
{
	if (!allow_clk_suspend(info) && new_state == CLOCK_SUSPEND)
		return;

	if (info->clk_state == CLOCK_ENABLE) {
		if (new_state != CLOCK_ENABLE)
			clk_disable_unprepare(info->clk);
	} else {
		if (new_state == CLOCK_ENABLE)
			clk_prepare_enable(info->clk);
	}

	info->clk_state = new_state;
}