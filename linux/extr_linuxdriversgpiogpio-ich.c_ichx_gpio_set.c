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
 int /*<<< orphan*/  GPIO_LVL ; 
 int /*<<< orphan*/  ichx_write_bit (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ichx_gpio_set(struct gpio_chip *chip, unsigned nr, int val)
{
	ichx_write_bit(GPIO_LVL, nr, val, 0);
}