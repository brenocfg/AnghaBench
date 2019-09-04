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
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 struct gpio_desc* devm_gpiod_get_index (struct device*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static  int sharp_ls_get_gpio_of(struct device *dev, int index, int val,
	const char *desc, struct gpio_desc **gpiod)
{
	struct gpio_desc *gd;

	*gpiod = NULL;

	gd = devm_gpiod_get_index(dev, desc, index, GPIOD_OUT_LOW);
	if (IS_ERR(gd))
		return PTR_ERR(gd);

	*gpiod = gd;
	return 0;
}