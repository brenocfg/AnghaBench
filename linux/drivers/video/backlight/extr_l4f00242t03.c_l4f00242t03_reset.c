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
 int /*<<< orphan*/  gpio_set_value (unsigned int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void l4f00242t03_reset(unsigned int gpio)
{
	pr_debug("l4f00242t03_reset.\n");
	gpio_set_value(gpio, 1);
	mdelay(100);
	gpio_set_value(gpio, 0);
	mdelay(10);	/* tRES >= 100us */
	gpio_set_value(gpio, 1);
	mdelay(20);
}