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
struct wmt_pinctrl_data {void* ngroups; void* groups; void* npins; void* pins; void* nbanks; void* banks; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct wmt_pinctrl_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* vt8500_banks ; 
 void* vt8500_groups ; 
 void* vt8500_pins ; 
 int wmt_pinctrl_probe (struct platform_device*,struct wmt_pinctrl_data*) ; 

__attribute__((used)) static int vt8500_pinctrl_probe(struct platform_device *pdev)
{
	struct wmt_pinctrl_data *data;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->banks = vt8500_banks;
	data->nbanks = ARRAY_SIZE(vt8500_banks);
	data->pins = vt8500_pins;
	data->npins = ARRAY_SIZE(vt8500_pins);
	data->groups = vt8500_groups;
	data->ngroups = ARRAY_SIZE(vt8500_groups);

	return wmt_pinctrl_probe(pdev, data);
}