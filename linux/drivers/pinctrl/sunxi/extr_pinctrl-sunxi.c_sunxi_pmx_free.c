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
struct sunxi_pinctrl_regulator {int /*<<< orphan*/ * regulator; int /*<<< orphan*/  refcount; } ;
struct sunxi_pinctrl {struct sunxi_pinctrl_regulator* regulators; TYPE_1__* desc; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {unsigned int pin_base; } ;

/* Variables and functions */
 unsigned int PINS_PER_BANK ; 
 struct sunxi_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sunxi_pmx_free(struct pinctrl_dev *pctldev, unsigned offset)
{
	struct sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	unsigned short bank = offset / PINS_PER_BANK;
	unsigned short bank_offset = bank - pctl->desc->pin_base /
					    PINS_PER_BANK;
	struct sunxi_pinctrl_regulator *s_reg = &pctl->regulators[bank_offset];

	if (!refcount_dec_and_test(&s_reg->refcount))
		return 0;

	regulator_disable(s_reg->regulator);
	regulator_put(s_reg->regulator);
	s_reg->regulator = NULL;

	return 0;
}