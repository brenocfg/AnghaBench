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
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ has_key_backlight; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_KEY ; 
 int /*<<< orphan*/  applesmc_write_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  backlight_state ; 
 TYPE_1__ smcreg ; 

__attribute__((used)) static int applesmc_pm_resume(struct device *dev)
{
	if (smcreg.has_key_backlight)
		applesmc_write_key(BACKLIGHT_KEY, backlight_state, 2);
	return 0;
}