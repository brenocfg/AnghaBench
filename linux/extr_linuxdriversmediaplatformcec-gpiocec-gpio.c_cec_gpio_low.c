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
struct cec_gpio {int cec_is_low; int cec_have_irq; int /*<<< orphan*/  cec_gpio; int /*<<< orphan*/  cec_irq; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct cec_gpio* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cec_gpio*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cec_gpio_low(struct cec_adapter *adap)
{
	struct cec_gpio *cec = cec_get_drvdata(adap);

	if (cec->cec_is_low)
		return;
	if (WARN_ON_ONCE(cec->cec_have_irq))
		free_irq(cec->cec_irq, cec);
	cec->cec_have_irq = false;
	cec->cec_is_low = true;
	gpiod_set_value(cec->cec_gpio, 0);
}