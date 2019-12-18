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
struct hl_device {scalar_t__ pm_mng_profile; int curr_pll_profile; TYPE_1__* asic_funcs; int /*<<< orphan*/  dev; } ;
typedef  enum hl_pll_frequency { ____Placeholder_hl_pll_frequency } hl_pll_frequency ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_pll_profile ) (struct hl_device*,int) ;} ;

/* Variables and functions */
 int PLL_HIGH ; 
 scalar_t__ PM_MANUAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int) ; 

int hl_device_set_frequency(struct hl_device *hdev, enum hl_pll_frequency freq)
{
	if ((hdev->pm_mng_profile == PM_MANUAL) ||
			(hdev->curr_pll_profile == freq))
		return 0;

	dev_dbg(hdev->dev, "Changing device frequency to %s\n",
		freq == PLL_HIGH ? "high" : "low");

	hdev->asic_funcs->set_pll_profile(hdev, freq);

	hdev->curr_pll_profile = freq;

	return 1;
}