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
struct lm3630a_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  work; int /*<<< orphan*/  irqthread; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_DEBOUNCE_MSEC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  REG_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lm3630a_update (struct lm3630a_chip*,int /*<<< orphan*/ ,int,int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t lm3630a_isr_func(int irq, void *chip)
{
	int rval;
	struct lm3630a_chip *pchip = chip;
	unsigned long delay = msecs_to_jiffies(INT_DEBOUNCE_MSEC);

	queue_delayed_work(pchip->irqthread, &pchip->work, delay);

	rval = lm3630a_update(pchip, REG_CTRL, 0x80, 0x00);
	if (rval < 0) {
		dev_err(pchip->dev, "i2c failed to access register\n");
		return IRQ_NONE;
	}
	return IRQ_HANDLED;
}