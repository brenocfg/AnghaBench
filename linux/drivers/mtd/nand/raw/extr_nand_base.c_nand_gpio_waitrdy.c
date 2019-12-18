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
struct nand_chip {int dummy; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ gpiod_get_value_cansleep (struct gpio_desc*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

int nand_gpio_waitrdy(struct nand_chip *chip, struct gpio_desc *gpiod,
		      unsigned long timeout_ms)
{
	/* Wait until R/B pin indicates chip is ready or timeout occurs */
	timeout_ms = jiffies + msecs_to_jiffies(timeout_ms);
	do {
		if (gpiod_get_value_cansleep(gpiod))
			return 0;

		cond_resched();
	} while	(time_before(jiffies, timeout_ms));

	return gpiod_get_value_cansleep(gpiod) ? 0 : -ETIMEDOUT;
}