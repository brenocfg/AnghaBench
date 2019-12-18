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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ddc {int /*<<< orphan*/  pin_clock; } ;
struct dc_link {int /*<<< orphan*/  ddc; int /*<<< orphan*/  link_id; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
typedef  enum connector_id { ____Placeholder_connector_id } connector_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int CONNECTOR_ID_DISPLAY_PORT ; 
 int CONNECTOR_ID_EDP ; 
 int /*<<< orphan*/  GPIO_DDC_CONFIG_TYPE_MODE_I2C ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT ; 
 scalar_t__ GPIO_RESULT_OK ; 
 int /*<<< orphan*/  dal_ddc_close (struct ddc*) ; 
 scalar_t__ dal_ddc_open (struct ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ddc* dal_ddc_service_get_ddc_pin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dal_gpio_destroy_ddc (struct ddc**) ; 
 int dal_gpio_get_value (int /*<<< orphan*/ ,scalar_t__*) ; 
 int dal_graphics_object_id_get_connector_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool dc_link_is_dp_sink_present(struct dc_link *link)
{
	enum gpio_result gpio_result;
	uint32_t clock_pin = 0;
	uint8_t retry = 0;
	struct ddc *ddc;

	enum connector_id connector_id =
		dal_graphics_object_id_get_connector_id(link->link_id);

	bool present =
		((connector_id == CONNECTOR_ID_DISPLAY_PORT) ||
		(connector_id == CONNECTOR_ID_EDP));

	ddc = dal_ddc_service_get_ddc_pin(link->ddc);

	if (!ddc) {
		BREAK_TO_DEBUGGER();
		return present;
	}

	/* Open GPIO and set it to I2C mode */
	/* Note: this GpioMode_Input will be converted
	 * to GpioConfigType_I2cAuxDualMode in GPIO component,
	 * which indicates we need additional delay */

	if (GPIO_RESULT_OK != dal_ddc_open(
		ddc, GPIO_MODE_INPUT, GPIO_DDC_CONFIG_TYPE_MODE_I2C)) {
		dal_gpio_destroy_ddc(&ddc);

		return present;
	}

	/*
	 * Read GPIO: DP sink is present if both clock and data pins are zero
	 *
	 * [W/A] plug-unplug DP cable, sometimes customer board has
	 * one short pulse on clk_pin(1V, < 1ms). DP will be config to HDMI/DVI
	 * then monitor can't br light up. Add retry 3 times
	 * But in real passive dongle, it need additional 3ms to detect
	 */
	do {
		gpio_result = dal_gpio_get_value(ddc->pin_clock, &clock_pin);
		ASSERT(gpio_result == GPIO_RESULT_OK);
		if (clock_pin)
			udelay(1000);
		else
			break;
	} while (retry++ < 3);

	present = (gpio_result == GPIO_RESULT_OK) && !clock_pin;

	dal_ddc_close(ddc);

	return present;
}