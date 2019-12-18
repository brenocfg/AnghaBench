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
typedef  int /*<<< orphan*/  uint32_t ;
struct vega12_hwmgr {TYPE_1__* clk_range; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_2__ {int /*<<< orphan*/  ACMin; int /*<<< orphan*/  ACMax; } ;
typedef  size_t PPCLK_e ;

/* Variables and functions */

__attribute__((used)) static int vega12_get_clock_ranges(struct pp_hwmgr *hwmgr,
		uint32_t *clock,
		PPCLK_e clock_select,
		bool max)
{
	struct vega12_hwmgr *data = (struct vega12_hwmgr *)(hwmgr->backend);

	if (max)
		*clock = data->clk_range[clock_select].ACMax;
	else
		*clock = data->clk_range[clock_select].ACMin;

	return 0;
}