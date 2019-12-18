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
 int GPIOD_FLAGS_BIT_NONEXCLUSIVE ; 
 int GPIOD_OUT_LOW ; 
#define  LM36274_LDO_NEG 131 
#define  LM36274_LDO_POS 130 
#define  LM3632_LDO_NEG 129 
#define  LM3632_LDO_POS 128 
 struct gpio_desc* gpiod_get_index_optional (struct device*,char*,int,int) ; 

__attribute__((used)) static struct gpio_desc *lm363x_regulator_of_get_enable_gpio(struct device *dev, int id)
{
	/*
	 * Check LCM_EN1/2_GPIO is configured.
	 * Those pins are used for enabling VPOS/VNEG LDOs.
	 * Do not use devm* here: the regulator core takes over the
	 * lifecycle management of the GPIO descriptor.
	 */
	switch (id) {
	case LM3632_LDO_POS:
	case LM36274_LDO_POS:
		return gpiod_get_index_optional(dev, "enable", 0,
				GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	case LM3632_LDO_NEG:
	case LM36274_LDO_NEG:
		return gpiod_get_index_optional(dev, "enable", 1,
				GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	default:
		return NULL;
	}
}