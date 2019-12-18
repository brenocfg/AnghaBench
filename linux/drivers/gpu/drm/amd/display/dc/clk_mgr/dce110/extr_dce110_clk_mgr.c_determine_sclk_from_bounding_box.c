#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_levels; int* clocks_in_khz; } ;
struct dc {TYPE_1__ sclk_lvls; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int determine_sclk_from_bounding_box(
		const struct dc *dc,
		int required_sclk)
{
	int i;

	/*
	 * Some asics do not give us sclk levels, so we just report the actual
	 * required sclk
	 */
	if (dc->sclk_lvls.num_levels == 0)
		return required_sclk;

	for (i = 0; i < dc->sclk_lvls.num_levels; i++) {
		if (dc->sclk_lvls.clocks_in_khz[i] >= required_sclk)
			return dc->sclk_lvls.clocks_in_khz[i];
	}
	/*
	 * even maximum level could not satisfy requirement, this
	 * is unexpected at this stage, should have been caught at
	 * validation time
	 */
	ASSERT(0);
	return dc->sclk_lvls.clocks_in_khz[dc->sclk_lvls.num_levels - 1];
}