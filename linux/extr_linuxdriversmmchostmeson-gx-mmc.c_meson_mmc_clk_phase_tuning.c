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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_host {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int CLK_PHASE_POINT_NUM ; 
 int CLK_PHASE_STEP ; 
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __clk_get_name (struct clk*) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_get_phase (struct clk*) ; 
 int /*<<< orphan*/  clk_set_phase (struct clk*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int meson_mmc_find_tuning_point (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int mmc_send_tuning (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test ; 

__attribute__((used)) static int meson_mmc_clk_phase_tuning(struct mmc_host *mmc, u32 opcode,
				      struct clk *clk)
{
	int point, ret;
	DECLARE_BITMAP(test, CLK_PHASE_POINT_NUM);

	dev_dbg(mmc_dev(mmc), "%s phase/delay tunning...\n",
		__clk_get_name(clk));
	bitmap_zero(test, CLK_PHASE_POINT_NUM);

	/* Explore tuning points */
	for (point = 0; point < CLK_PHASE_POINT_NUM; point++) {
		clk_set_phase(clk, point * CLK_PHASE_STEP);
		ret = mmc_send_tuning(mmc, opcode, NULL);
		if (!ret)
			set_bit(point, test);
	}

	/* Find the optimal tuning point and apply it */
	point = meson_mmc_find_tuning_point(test);
	if (point < 0)
		return point; /* tuning failed */

	clk_set_phase(clk, point * CLK_PHASE_STEP);
	dev_dbg(mmc_dev(mmc), "success with phase: %d\n",
		clk_get_phase(clk));
	return 0;
}