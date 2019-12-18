#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hw_hpd {int dummy; } ;
struct hw_gpio_pin {int dummy; } ;
struct TYPE_3__ {int delay_on_connect; int delay_on_disconnect; } ;
struct TYPE_4__ {TYPE_1__ hpd; } ;
struct gpio_config_data {TYPE_2__ config; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;

/* Variables and functions */
 int /*<<< orphan*/  DC_HPD_CONNECT_INT_DELAY ; 
 int /*<<< orphan*/  DC_HPD_DISCONNECT_INT_DELAY ; 
 int GPIO_RESULT_INVALID_DATA ; 
 int GPIO_RESULT_OK ; 
 struct hw_hpd* HW_HPD_FROM_BASE (struct hw_gpio_pin*) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  toggle_filt_cntl ; 

__attribute__((used)) static enum gpio_result set_config(
	struct hw_gpio_pin *ptr,
	const struct gpio_config_data *config_data)
{
	struct hw_hpd *hpd = HW_HPD_FROM_BASE(ptr);

	if (!config_data)
		return GPIO_RESULT_INVALID_DATA;

	REG_UPDATE_2(toggle_filt_cntl,
		DC_HPD_CONNECT_INT_DELAY, config_data->config.hpd.delay_on_connect / 10,
		DC_HPD_DISCONNECT_INT_DELAY, config_data->config.hpd.delay_on_disconnect / 10);

	return GPIO_RESULT_OK;
}