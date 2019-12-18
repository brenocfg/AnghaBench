#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct axp20x_pctl {TYPE_1__* desc; TYPE_2__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {char* name; int ngroups; int /*<<< orphan*/ * groups; int /*<<< orphan*/  muxval; } ;
struct TYPE_4__ {int npins; TYPE_3__* pins; int /*<<< orphan*/  adc_mask; int /*<<< orphan*/  ldo_mask; int /*<<< orphan*/  adc_mux; } ;

/* Variables and functions */
 size_t AXP20X_FUNC_ADC ; 
 size_t AXP20X_FUNC_GPIO_IN ; 
 size_t AXP20X_FUNC_GPIO_OUT ; 
 size_t AXP20X_FUNC_LDO ; 
 int /*<<< orphan*/  AXP20X_MUX_GPIO_IN ; 
 int /*<<< orphan*/  AXP20X_MUX_GPIO_OUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int axp20x_funcs_groups_from_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct axp20x_pctl* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int axp20x_build_funcs_groups(struct platform_device *pdev)
{
	struct axp20x_pctl *pctl = platform_get_drvdata(pdev);
	int i, ret, pin, npins = pctl->desc->npins;

	pctl->funcs[AXP20X_FUNC_GPIO_OUT].name = "gpio_out";
	pctl->funcs[AXP20X_FUNC_GPIO_OUT].muxval = AXP20X_MUX_GPIO_OUT;
	pctl->funcs[AXP20X_FUNC_GPIO_IN].name = "gpio_in";
	pctl->funcs[AXP20X_FUNC_GPIO_IN].muxval = AXP20X_MUX_GPIO_IN;
	pctl->funcs[AXP20X_FUNC_LDO].name = "ldo";
	/*
	 * Muxval for LDO is useless as we won't use it.
	 * See comment in axp20x_pmx_set_mux.
	 */
	pctl->funcs[AXP20X_FUNC_ADC].name = "adc";
	pctl->funcs[AXP20X_FUNC_ADC].muxval = pctl->desc->adc_mux;

	/* Every pin supports GPIO_OUT and GPIO_IN functions */
	for (i = 0; i <= AXP20X_FUNC_GPIO_IN; i++) {
		pctl->funcs[i].ngroups = npins;
		pctl->funcs[i].groups = devm_kcalloc(&pdev->dev,
						     npins, sizeof(char *),
						     GFP_KERNEL);
		if (!pctl->funcs[i].groups)
			return -ENOMEM;
		for (pin = 0; pin < npins; pin++)
			pctl->funcs[i].groups[pin] = pctl->desc->pins[pin].name;
	}

	ret = axp20x_funcs_groups_from_mask(&pdev->dev, pctl->desc->ldo_mask,
				      npins, &pctl->funcs[AXP20X_FUNC_LDO],
				      pctl->desc->pins);
	if (ret)
		return ret;

	ret = axp20x_funcs_groups_from_mask(&pdev->dev, pctl->desc->adc_mask,
				      npins, &pctl->funcs[AXP20X_FUNC_ADC],
				      pctl->desc->pins);
	if (ret)
		return ret;

	return 0;
}