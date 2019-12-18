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
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR_OR_NULL (struct gpio_desc*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devm_gpiod_match ; 
 int /*<<< orphan*/  devm_gpiod_release ; 
 int devres_destroy (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_desc**) ; 

void devm_gpiod_unhinge(struct device *dev, struct gpio_desc *desc)
{
	int ret;

	if (IS_ERR_OR_NULL(desc))
		return;
	ret = devres_destroy(dev, devm_gpiod_release,
			     devm_gpiod_match, &desc);
	/*
	 * If the GPIO descriptor is requested as nonexclusive, we
	 * may call this function several times on the same descriptor
	 * so it is OK if devres_destroy() returns -ENOENT.
	 */
	if (ret == -ENOENT)
		return;
	/* Anything else we should warn about */
	WARN_ON(ret);
}