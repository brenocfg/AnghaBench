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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct byt_gpio {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  byt_gpio_clear_triggering (struct byt_gpio*,unsigned int) ; 
 struct byt_gpio* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void byt_gpio_disable_free(struct pinctrl_dev *pctl_dev,
				  struct pinctrl_gpio_range *range,
				  unsigned int offset)
{
	struct byt_gpio *vg = pinctrl_dev_get_drvdata(pctl_dev);

	byt_gpio_clear_triggering(vg, offset);
	pm_runtime_put(&vg->pdev->dev);
}