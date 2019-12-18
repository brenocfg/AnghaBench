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
struct pinctrl_gpio_range {int /*<<< orphan*/  gc; } ;
struct pinctrl_dev {int dummy; } ;
struct npcm7xx_pinctrl {int /*<<< orphan*/  gcr_regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fn_gpio ; 
 int /*<<< orphan*/  npcm7xx_setfunc (int /*<<< orphan*/ ,unsigned int*,int,int /*<<< orphan*/ ) ; 
 struct npcm7xx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int npcm7xx_gpio_request_enable(struct pinctrl_dev *pctldev,
				       struct pinctrl_gpio_range *range,
				       unsigned int offset)
{
	struct npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);

	if (!range) {
		dev_err(npcm->dev, "invalid range\n");
		return -EINVAL;
	}
	if (!range->gc) {
		dev_err(npcm->dev, "invalid gpiochip\n");
		return -EINVAL;
	}

	npcm7xx_setfunc(npcm->gcr_regmap, &offset, 1, fn_gpio);

	return 0;
}