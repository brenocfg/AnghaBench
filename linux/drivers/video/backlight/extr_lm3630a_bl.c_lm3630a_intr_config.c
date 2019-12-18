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
struct lm3630a_chip {int /*<<< orphan*/  irqthread; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  REG_INT_EN ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lm3630a_delayed_func ; 
 int /*<<< orphan*/  lm3630a_isr_func ; 
 int lm3630a_write (struct lm3630a_chip*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct lm3630a_chip*) ; 

__attribute__((used)) static int lm3630a_intr_config(struct lm3630a_chip *pchip)
{
	int rval;

	rval = lm3630a_write(pchip, REG_INT_EN, 0x87);
	if (rval < 0)
		return rval;

	INIT_DELAYED_WORK(&pchip->work, lm3630a_delayed_func);
	pchip->irqthread = create_singlethread_workqueue("lm3630a-irqthd");
	if (!pchip->irqthread) {
		dev_err(pchip->dev, "create irq thread fail\n");
		return -ENOMEM;
	}
	if (request_threaded_irq
	    (pchip->irq, NULL, lm3630a_isr_func,
	     IRQF_TRIGGER_FALLING | IRQF_ONESHOT, "lm3630a_irq", pchip)) {
		dev_err(pchip->dev, "request threaded irq fail\n");
		destroy_workqueue(pchip->irqthread);
		return -ENOMEM;
	}
	return rval;
}