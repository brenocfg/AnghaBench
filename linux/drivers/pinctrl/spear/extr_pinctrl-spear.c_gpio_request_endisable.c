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
struct spear_pmx {struct spear_pinctrl_machdata* machdata; } ;
struct spear_pinctrl_machdata {int /*<<< orphan*/  (* gpio_request_endisable ) (struct spear_pmx*,unsigned int,int) ;} ;
struct spear_gpio_pingroup {int /*<<< orphan*/  nmuxregs; int /*<<< orphan*/  muxregs; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct spear_gpio_pingroup* get_gpio_pingroup (struct spear_pmx*,unsigned int) ; 
 int /*<<< orphan*/  muxregs_endisable (struct spear_pmx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct spear_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  stub1 (struct spear_pmx*,unsigned int,int) ; 

__attribute__((used)) static int gpio_request_endisable(struct pinctrl_dev *pctldev,
		struct pinctrl_gpio_range *range, unsigned offset, bool enable)
{
	struct spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	struct spear_pinctrl_machdata *machdata = pmx->machdata;
	struct spear_gpio_pingroup *gpio_pingroup;

	/*
	 * Some SoC have configuration options applicable to group of pins,
	 * rather than a single pin.
	 */
	gpio_pingroup = get_gpio_pingroup(pmx, offset);
	if (gpio_pingroup)
		muxregs_endisable(pmx, gpio_pingroup->muxregs,
				gpio_pingroup->nmuxregs, enable);

	/*
	 * SoC may need some extra configurations, or configurations for single
	 * pin
	 */
	if (machdata->gpio_request_endisable)
		machdata->gpio_request_endisable(pmx, offset, enable);

	return 0;
}