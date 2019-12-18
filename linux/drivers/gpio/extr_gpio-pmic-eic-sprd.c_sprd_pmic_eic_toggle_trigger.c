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
typedef  int u32 ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int IRQ_TYPE_EDGE_BOTH ; 
 int /*<<< orphan*/  SPRD_PMIC_EIC_IE ; 
 int /*<<< orphan*/  SPRD_PMIC_EIC_IEV ; 
 int /*<<< orphan*/  SPRD_PMIC_EIC_TRIG ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int irq_get_trigger_type (unsigned int) ; 
 int sprd_pmic_eic_get (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  sprd_pmic_eic_update (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sprd_pmic_eic_toggle_trigger(struct gpio_chip *chip,
					 unsigned int irq, unsigned int offset)
{
	u32 trigger = irq_get_trigger_type(irq);
	int state, post_state;

	if (!(trigger & IRQ_TYPE_EDGE_BOTH))
		return;

	state = sprd_pmic_eic_get(chip, offset);
retry:
	if (state)
		sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IEV, 0);
	else
		sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IEV, 1);

	post_state = sprd_pmic_eic_get(chip, offset);
	if (state != post_state) {
		dev_warn(chip->parent, "PMIC EIC level was changed.\n");
		state = post_state;
		goto retry;
	}

	/* Set irq unmask */
	sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_IE, 1);
	/* Generate trigger start pulse for debounce EIC */
	sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_TRIG, 1);
}