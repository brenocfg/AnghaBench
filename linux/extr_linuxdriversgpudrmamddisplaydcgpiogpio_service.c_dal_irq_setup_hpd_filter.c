#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_hpd_config {int dummy; } ;
struct TYPE_2__ {struct gpio_hpd_config hpd; } ;
struct gpio_config_data {TYPE_1__ config; int /*<<< orphan*/  type; } ;
struct gpio {int dummy; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CONFIG_TYPE_HPD ; 
 int GPIO_RESULT_INVALID_DATA ; 
 int dal_gpio_set_config (struct gpio*,struct gpio_config_data*) ; 

enum gpio_result dal_irq_setup_hpd_filter(
	struct gpio *irq,
	struct gpio_hpd_config *config)
{
	struct gpio_config_data config_data;

	if (!config)
		return GPIO_RESULT_INVALID_DATA;

	config_data.type = GPIO_CONFIG_TYPE_HPD;
	config_data.config.hpd = *config;

	return dal_gpio_set_config(irq, &config_data);
}