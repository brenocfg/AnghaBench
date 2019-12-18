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
typedef  size_t u32 ;
struct pinctrl_gpio_range {size_t npins; size_t* pins; } ;
struct pinctrl_dev {int dummy; } ;
struct atlas7_pmx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  FUNC_GPIO ; 
 int /*<<< orphan*/  __atlas7_pmx_pin_enable (struct atlas7_pmx*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 struct atlas7_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int atlas7_pmx_gpio_request_enable(struct pinctrl_dev *pctldev,
		struct pinctrl_gpio_range *range, u32 pin)
{
	struct atlas7_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	u32 idx;

	dev_dbg(pmx->dev,
		"atlas7_pmx_gpio_request_enable: pin=%d\n", pin);
	for (idx = 0; idx < range->npins; idx++) {
		if (pin == range->pins[idx])
			break;
	}

	if (idx >= range->npins) {
		dev_err(pmx->dev,
			"The pin#%d could not be requested as GPIO!!\n",
			pin);
		return -EPERM;
	}

	__atlas7_pmx_pin_enable(pmx, pin, FUNC_GPIO);

	return 0;
}