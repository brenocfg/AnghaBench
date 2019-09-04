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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,char const*) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  gpio_unexport (int) ; 

__attribute__((used)) static void vip_gpio_release(struct device *dev, int pin, const char *name)
{
	if (gpio_is_valid(pin)) {
		dev_dbg(dev, "releasing pin %d (%s)\n",	pin, name);
		gpio_unexport(pin);
		gpio_free(pin);
	}
}