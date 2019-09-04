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
struct cec_gpio {int cec_have_irq; int /*<<< orphan*/  cec_irq; } ;
struct cec_adapter {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 struct cec_gpio* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_gpio_irq_handler ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct cec_gpio*) ; 

__attribute__((used)) static bool cec_gpio_enable_irq(struct cec_adapter *adap)
{
	struct cec_gpio *cec = cec_get_drvdata(adap);

	if (cec->cec_have_irq)
		return true;

	if (request_irq(cec->cec_irq, cec_gpio_irq_handler,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			adap->name, cec))
		return false;
	cec->cec_have_irq = true;
	return true;
}