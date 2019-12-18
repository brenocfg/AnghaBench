#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_pfc {int* irqs; TYPE_1__* info; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_4__ {short* gpios; } ;
struct TYPE_3__ {unsigned int gpio_irq_size; TYPE_2__* gpio_irq; } ;

/* Variables and functions */
 struct sh_pfc* gpio_to_pfc (struct gpio_chip*) ; 

__attribute__((used)) static int gpio_pin_to_irq(struct gpio_chip *gc, unsigned offset)
{
	struct sh_pfc *pfc = gpio_to_pfc(gc);
	unsigned int i, k;

	for (i = 0; i < pfc->info->gpio_irq_size; i++) {
		const short *gpios = pfc->info->gpio_irq[i].gpios;

		for (k = 0; gpios[k] >= 0; k++) {
			if (gpios[k] == offset)
				goto found;
		}
	}

	return 0;

found:
	return pfc->irqs[i];
}