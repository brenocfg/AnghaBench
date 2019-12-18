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
struct picolcd_data {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_BRIGHTNESS ; 
 int /*<<< orphan*/  REPORT_CONTRAST ; 
 int /*<<< orphan*/  REPORT_EE_READ ; 
 int /*<<< orphan*/  REPORT_EE_WRITE ; 
 int /*<<< orphan*/  REPORT_IR_DATA ; 
 int /*<<< orphan*/  REPORT_KEY_STATE ; 
 int /*<<< orphan*/  REPORT_LED_STATE ; 
 int /*<<< orphan*/  REPORT_READ_MEMORY ; 
 int /*<<< orphan*/  REPORT_RESET ; 
 int /*<<< orphan*/  REPORT_WRITE_MEMORY ; 
 int /*<<< orphan*/  picolcd_exit_backlight (struct picolcd_data*) ; 
 int /*<<< orphan*/  picolcd_exit_cir (struct picolcd_data*) ; 
 int /*<<< orphan*/  picolcd_exit_framebuffer (struct picolcd_data*) ; 
 int /*<<< orphan*/  picolcd_exit_keys (struct picolcd_data*) ; 
 int /*<<< orphan*/  picolcd_exit_lcd (struct picolcd_data*) ; 
 int /*<<< orphan*/  picolcd_exit_leds (struct picolcd_data*) ; 
 int /*<<< orphan*/  picolcd_in_report (int /*<<< orphan*/ ,struct hid_device*) ; 
 int picolcd_init_backlight (struct picolcd_data*,int /*<<< orphan*/ ) ; 
 int picolcd_init_cir (struct picolcd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picolcd_init_devfs (struct picolcd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int picolcd_init_framebuffer (struct picolcd_data*) ; 
 int picolcd_init_keys (struct picolcd_data*,int /*<<< orphan*/ ) ; 
 int picolcd_init_lcd (struct picolcd_data*,int /*<<< orphan*/ ) ; 
 int picolcd_init_leds (struct picolcd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picolcd_out_report (int /*<<< orphan*/ ,struct hid_device*) ; 

__attribute__((used)) static int picolcd_probe_lcd(struct hid_device *hdev, struct picolcd_data *data)
{
	int error;

	/* Setup keypad input device */
	error = picolcd_init_keys(data, picolcd_in_report(REPORT_KEY_STATE, hdev));
	if (error)
		goto err;

	/* Setup CIR input device */
	error = picolcd_init_cir(data, picolcd_in_report(REPORT_IR_DATA, hdev));
	if (error)
		goto err;

	/* Set up the framebuffer device */
	error = picolcd_init_framebuffer(data);
	if (error)
		goto err;

	/* Setup lcd class device */
	error = picolcd_init_lcd(data, picolcd_out_report(REPORT_CONTRAST, hdev));
	if (error)
		goto err;

	/* Setup backlight class device */
	error = picolcd_init_backlight(data, picolcd_out_report(REPORT_BRIGHTNESS, hdev));
	if (error)
		goto err;

	/* Setup the LED class devices */
	error = picolcd_init_leds(data, picolcd_out_report(REPORT_LED_STATE, hdev));
	if (error)
		goto err;

	picolcd_init_devfs(data, picolcd_out_report(REPORT_EE_READ, hdev),
			picolcd_out_report(REPORT_EE_WRITE, hdev),
			picolcd_out_report(REPORT_READ_MEMORY, hdev),
			picolcd_out_report(REPORT_WRITE_MEMORY, hdev),
			picolcd_out_report(REPORT_RESET, hdev));
	return 0;
err:
	picolcd_exit_leds(data);
	picolcd_exit_backlight(data);
	picolcd_exit_lcd(data);
	picolcd_exit_framebuffer(data);
	picolcd_exit_cir(data);
	picolcd_exit_keys(data);
	return error;
}