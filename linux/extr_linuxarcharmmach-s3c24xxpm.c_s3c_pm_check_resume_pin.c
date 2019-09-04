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

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_GPIO_INPUT ; 
 unsigned long S3C2410_GPIO_IRQ ; 
 int /*<<< orphan*/  S3C_PMDBG (char*,int,unsigned int) ; 
 int gpio_to_irq (unsigned int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long s3c_gpio_getcfg (unsigned int) ; 
 long s3c_irqwake_eintmask ; 
 long s3c_irqwake_intmask ; 

__attribute__((used)) static void s3c_pm_check_resume_pin(unsigned int pin, unsigned int irqoffs)
{
	unsigned long irqstate;
	unsigned long pinstate;
	int irq = gpio_to_irq(pin);

	if (irqoffs < 4)
		irqstate = s3c_irqwake_intmask & (1L<<irqoffs);
	else
		irqstate = s3c_irqwake_eintmask & (1L<<irqoffs);

	pinstate = s3c_gpio_getcfg(pin);

	if (!irqstate) {
		if (pinstate == S3C2410_GPIO_IRQ)
			S3C_PMDBG("Leaving IRQ %d (pin %d) as is\n", irq, pin);
	} else {
		if (pinstate == S3C2410_GPIO_IRQ) {
			S3C_PMDBG("Disabling IRQ %d (pin %d)\n", irq, pin);
			s3c_gpio_cfgpin(pin, S3C2410_GPIO_INPUT);
		}
	}
}