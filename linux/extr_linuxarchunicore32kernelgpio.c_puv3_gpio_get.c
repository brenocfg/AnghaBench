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

/* Variables and functions */
 int GPIO_GPIO (unsigned int) ; 
 int /*<<< orphan*/  GPIO_GPLR ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	return !!(readl(GPIO_GPLR) & GPIO_GPIO(offset));
}