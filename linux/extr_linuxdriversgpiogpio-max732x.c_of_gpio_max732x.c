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
struct max732x_platform_data {int gpio_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct max732x_platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct max732x_platform_data *of_gpio_max732x(struct device *dev)
{
	struct max732x_platform_data *pdata;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	pdata->gpio_base = -1;

	return pdata;
}