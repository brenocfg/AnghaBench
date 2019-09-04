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
struct gpio_descs {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_match_array ; 
 int /*<<< orphan*/  devm_gpiod_release_array ; 
 int /*<<< orphan*/  devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_descs**) ; 

void devm_gpiod_put_array(struct device *dev, struct gpio_descs *descs)
{
	WARN_ON(devres_release(dev, devm_gpiod_release_array,
			       devm_gpiod_match_array, &descs));
}