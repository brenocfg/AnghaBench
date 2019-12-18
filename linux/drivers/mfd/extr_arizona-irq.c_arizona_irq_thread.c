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
struct TYPE_2__ {int irq_flags; int /*<<< orphan*/  irq_gpio; } ;
struct arizona {int /*<<< orphan*/  dev; TYPE_1__ pdata; int /*<<< orphan*/  virq; int /*<<< orphan*/  regmap; scalar_t__ aod_irq_chip; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_AOD_IRQ1 ; 
 unsigned int ARIZONA_IRQ1_STS ; 
 int /*<<< orphan*/  ARIZONA_IRQ_PIN_STATUS ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ gpio_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_nested_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t arizona_irq_thread(int irq, void *data)
{
	struct arizona *arizona = data;
	bool poll;
	unsigned int val;
	int ret;

	ret = pm_runtime_get_sync(arizona->dev);
	if (ret < 0) {
		dev_err(arizona->dev, "Failed to resume device: %d\n", ret);
		return IRQ_NONE;
	}

	do {
		poll = false;

		if (arizona->aod_irq_chip) {
			/*
			 * Check the AOD status register to determine whether
			 * the nested IRQ handler should be called.
			 */
			ret = regmap_read(arizona->regmap,
					  ARIZONA_AOD_IRQ1, &val);
			if (ret)
				dev_warn(arizona->dev,
					"Failed to read AOD IRQ1 %d\n", ret);
			else if (val)
				handle_nested_irq(
					irq_find_mapping(arizona->virq, 0));
		}

		/*
		 * Check if one of the main interrupts is asserted and only
		 * check that domain if it is.
		 */
		ret = regmap_read(arizona->regmap, ARIZONA_IRQ_PIN_STATUS,
				  &val);
		if (ret == 0 && val & ARIZONA_IRQ1_STS) {
			handle_nested_irq(irq_find_mapping(arizona->virq, 1));
		} else if (ret != 0) {
			dev_err(arizona->dev,
				"Failed to read main IRQ status: %d\n", ret);
		}

		/*
		 * Poll the IRQ pin status to see if we're really done
		 * if the interrupt controller can't do it for us.
		 */
		if (!arizona->pdata.irq_gpio) {
			break;
		} else if (arizona->pdata.irq_flags & IRQF_TRIGGER_RISING &&
			   gpio_get_value_cansleep(arizona->pdata.irq_gpio)) {
			poll = true;
		} else if (arizona->pdata.irq_flags & IRQF_TRIGGER_FALLING &&
			   !gpio_get_value_cansleep(arizona->pdata.irq_gpio)) {
			poll = true;
		}
	} while (poll);

	pm_runtime_mark_last_busy(arizona->dev);
	pm_runtime_put_autosuspend(arizona->dev);

	return IRQ_HANDLED;
}