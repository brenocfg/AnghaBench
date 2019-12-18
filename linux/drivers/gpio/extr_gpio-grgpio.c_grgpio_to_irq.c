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
struct grgpio_priv {int /*<<< orphan*/  domain; TYPE_1__* lirqs; } ;
struct gpio_chip {unsigned int ngpio; } ;
struct TYPE_2__ {scalar_t__ index; } ;

/* Variables and functions */
 int ENXIO ; 
 struct grgpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int grgpio_to_irq(struct gpio_chip *gc, unsigned offset)
{
	struct grgpio_priv *priv = gpiochip_get_data(gc);

	if (offset >= gc->ngpio)
		return -ENXIO;

	if (priv->lirqs[offset].index < 0)
		return -ENXIO;

	return irq_create_mapping(priv->domain, offset);
}