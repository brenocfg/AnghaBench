#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_4__ {int modes_supported; int /*<<< orphan*/  ngpio_pingroups; int /*<<< orphan*/  gpio_pingroups; void* nfunctions; void* functions; void* ngroups; void* groups; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  PMX_CONFIG_REG ; 
 int /*<<< orphan*/  pmx_init_addr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmx_init_gpio_pingroup_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* spear310_functions ; 
 void* spear310_pingroups ; 
 TYPE_1__ spear3xx_machdata ; 
 int spear_pinctrl_probe (struct platform_device*,TYPE_1__*) ; 

__attribute__((used)) static int spear310_pinctrl_probe(struct platform_device *pdev)
{
	int ret;

	spear3xx_machdata.groups = spear310_pingroups;
	spear3xx_machdata.ngroups = ARRAY_SIZE(spear310_pingroups);
	spear3xx_machdata.functions = spear310_functions;
	spear3xx_machdata.nfunctions = ARRAY_SIZE(spear310_functions);

	pmx_init_addr(&spear3xx_machdata, PMX_CONFIG_REG);
	pmx_init_gpio_pingroup_addr(spear3xx_machdata.gpio_pingroups,
			spear3xx_machdata.ngpio_pingroups, PMX_CONFIG_REG);

	spear3xx_machdata.modes_supported = false;

	ret = spear_pinctrl_probe(pdev, &spear3xx_machdata);
	if (ret)
		return ret;

	return 0;
}