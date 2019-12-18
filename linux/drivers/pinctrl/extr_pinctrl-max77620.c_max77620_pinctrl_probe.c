#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_7__* parent; int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct max77620_pctrl_info {int /*<<< orphan*/  pctl; TYPE_1__* fps_config; void* num_pin_groups; void* pin_groups; void* num_functions; void* functions; void* num_pins; void* pins; int /*<<< orphan*/  rmap; TYPE_3__* dev; } ;
struct max77620_chip {int /*<<< orphan*/  rmap; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_10__ {void* custom_params; void* num_custom_params; void* npins; void* pins; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int active_fps_src; int active_power_up_slots; int active_power_down_slots; int suspend_fps_src; int suspend_power_up_slots; int suspend_power_down_slots; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX77620_PIN_NUM ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct max77620_chip* dev_get_drvdata (TYPE_7__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 struct max77620_pctrl_info* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (TYPE_3__*,TYPE_2__*,struct max77620_pctrl_info*) ; 
 void* max77620_cfg_params ; 
 void* max77620_pin_function ; 
 TYPE_2__ max77620_pinctrl_desc ; 
 void* max77620_pingroups ; 
 void* max77620_pins_desc ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max77620_pctrl_info*) ; 

__attribute__((used)) static int max77620_pinctrl_probe(struct platform_device *pdev)
{
	struct max77620_chip *max77620 = dev_get_drvdata(pdev->dev.parent);
	struct max77620_pctrl_info *mpci;
	int i;

	mpci = devm_kzalloc(&pdev->dev, sizeof(*mpci), GFP_KERNEL);
	if (!mpci)
		return -ENOMEM;

	mpci->dev = &pdev->dev;
	mpci->dev->of_node = pdev->dev.parent->of_node;
	mpci->rmap = max77620->rmap;

	mpci->pins = max77620_pins_desc;
	mpci->num_pins = ARRAY_SIZE(max77620_pins_desc);
	mpci->functions = max77620_pin_function;
	mpci->num_functions = ARRAY_SIZE(max77620_pin_function);
	mpci->pin_groups = max77620_pingroups;
	mpci->num_pin_groups = ARRAY_SIZE(max77620_pingroups);
	platform_set_drvdata(pdev, mpci);

	max77620_pinctrl_desc.name = dev_name(&pdev->dev);
	max77620_pinctrl_desc.pins = max77620_pins_desc;
	max77620_pinctrl_desc.npins = ARRAY_SIZE(max77620_pins_desc);
	max77620_pinctrl_desc.num_custom_params =
				ARRAY_SIZE(max77620_cfg_params);
	max77620_pinctrl_desc.custom_params = max77620_cfg_params;

	for (i = 0; i < MAX77620_PIN_NUM; ++i) {
		mpci->fps_config[i].active_fps_src = -1;
		mpci->fps_config[i].active_power_up_slots = -1;
		mpci->fps_config[i].active_power_down_slots = -1;
		mpci->fps_config[i].suspend_fps_src = -1;
		mpci->fps_config[i].suspend_power_up_slots = -1;
		mpci->fps_config[i].suspend_power_down_slots = -1;
	}

	mpci->pctl = devm_pinctrl_register(&pdev->dev, &max77620_pinctrl_desc,
					   mpci);
	if (IS_ERR(mpci->pctl)) {
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		return PTR_ERR(mpci->pctl);
	}

	return 0;
}