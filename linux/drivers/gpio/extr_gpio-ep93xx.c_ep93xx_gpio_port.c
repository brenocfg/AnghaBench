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
struct gpio_chip {int dummy; } ;
struct ep93xx_gpio {struct gpio_chip* gc; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct gpio_chip*) ; 
 struct ep93xx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static int ep93xx_gpio_port(struct gpio_chip *gc)
{
	struct ep93xx_gpio *epg = gpiochip_get_data(gc);
	int port = 0;

	while (port < ARRAY_SIZE(epg->gc) && gc != &epg->gc[port])
		port++;

	/* This should not happen but is there as a last safeguard */
	if (port == ARRAY_SIZE(epg->gc)) {
		pr_crit("can't find the GPIO port\n");
		return 0;
	}

	return port;
}