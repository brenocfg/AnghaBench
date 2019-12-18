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
struct gpio_service {int dummy; } ;
struct gpio_pin_info {int mask; int offset; } ;
struct gpio_generic_mux_config {int enable_output_from_mux; int /*<<< orphan*/  mux_select; } ;
struct gpio {int dummy; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIO_ID_GENERIC ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT ; 
 int GPIO_RESULT_NON_SPECIFIC_ERROR ; 
 int GPIO_RESULT_OK ; 
 int /*<<< orphan*/  GPIO_SIGNAL_SOURCE_PASS_THROUGH_STEREO_SYNC ; 
 int /*<<< orphan*/  dal_gpio_close (struct gpio*) ; 
 int /*<<< orphan*/  dal_gpio_destroy_generic_mux (struct gpio**) ; 
 struct gpio_pin_info dal_gpio_get_generic_pin_info (struct gpio_service*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dal_gpio_open (struct gpio*,int /*<<< orphan*/ ) ; 
 struct gpio* dal_gpio_service_create_generic_mux (struct gpio_service*,int,int) ; 
 int dal_mux_setup_config (struct gpio*,struct gpio_generic_mux_config*) ; 
 int /*<<< orphan*/  kfree (struct gpio_generic_mux_config*) ; 
 struct gpio_generic_mux_config* kzalloc (int,int /*<<< orphan*/ ) ; 

bool dc_set_generic_gpio_for_stereo(bool enable,
		struct gpio_service *gpio_service)
{
	enum gpio_result gpio_result = GPIO_RESULT_NON_SPECIFIC_ERROR;
	struct gpio_pin_info pin_info;
	struct gpio *generic;
	struct gpio_generic_mux_config *config = kzalloc(sizeof(struct gpio_generic_mux_config),
			   GFP_KERNEL);

	if (!config)
		return false;
	pin_info = dal_gpio_get_generic_pin_info(gpio_service, GPIO_ID_GENERIC, 0);

	if (pin_info.mask == 0xFFFFFFFF || pin_info.offset == 0xFFFFFFFF) {
		kfree(config);
		return false;
	} else {
		generic = dal_gpio_service_create_generic_mux(
			gpio_service,
			pin_info.offset,
			pin_info.mask);
	}

	if (!generic) {
		kfree(config);
		return false;
	}

	gpio_result = dal_gpio_open(generic, GPIO_MODE_OUTPUT);

	config->enable_output_from_mux = enable;
	config->mux_select = GPIO_SIGNAL_SOURCE_PASS_THROUGH_STEREO_SYNC;

	if (gpio_result == GPIO_RESULT_OK)
		gpio_result = dal_mux_setup_config(generic, config);

	if (gpio_result == GPIO_RESULT_OK) {
		dal_gpio_close(generic);
		dal_gpio_destroy_generic_mux(&generic);
		kfree(config);
		return true;
	} else {
		dal_gpio_close(generic);
		dal_gpio_destroy_generic_mux(&generic);
		kfree(config);
		return false;
	}
}