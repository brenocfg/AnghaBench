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
struct geni_se {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  geni_se_clks_off (struct geni_se*) ; 
 int geni_se_clks_on (struct geni_se*) ; 
 scalar_t__ has_acpi_companion (int /*<<< orphan*/ ) ; 
 int pinctrl_pm_select_default_state (int /*<<< orphan*/ ) ; 

int geni_se_resources_on(struct geni_se *se)
{
	int ret;

	if (has_acpi_companion(se->dev))
		return 0;

	ret = geni_se_clks_on(se);
	if (ret)
		return ret;

	ret = pinctrl_pm_select_default_state(se->dev);
	if (ret)
		geni_se_clks_off(se);

	return ret;
}