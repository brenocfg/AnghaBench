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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_pinctrl_soc_data {int dummy; } ;

/* Variables and functions */
 struct intel_pinctrl_soc_data* device_get_match_data (int /*<<< orphan*/ *) ; 
 int intel_pinctrl_probe (struct platform_device*,struct intel_pinctrl_soc_data const*) ; 

int intel_pinctrl_probe_by_hid(struct platform_device *pdev)
{
	const struct intel_pinctrl_soc_data *data;

	data = device_get_match_data(&pdev->dev);
	return intel_pinctrl_probe(pdev, data);
}