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
struct cec_gpio {int /*<<< orphan*/  cec_gpio; int /*<<< orphan*/  adap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cec_pin_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t cec_gpio_irq_handler(int irq, void *priv)
{
	struct cec_gpio *cec = priv;

	cec_pin_changed(cec->adap, gpiod_get_value(cec->cec_gpio));
	return IRQ_HANDLED;
}