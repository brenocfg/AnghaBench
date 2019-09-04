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
struct cec_gpio {int hpd_is_high; int /*<<< orphan*/  hpd_ts; int /*<<< orphan*/  hpd_gpio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static irqreturn_t cec_hpd_gpio_irq_handler(int irq, void *priv)
{
	struct cec_gpio *cec = priv;
	bool is_high = gpiod_get_value(cec->hpd_gpio);

	if (is_high == cec->hpd_is_high)
		return IRQ_HANDLED;
	cec->hpd_ts = ktime_get();
	cec->hpd_is_high = is_high;
	return IRQ_WAKE_THREAD;
}