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
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HX8357_EXIT_SLEEP_MODE ; 
 int /*<<< orphan*/  HX8357_SET_DISPLAY_ON ; 
 int hx8357_spi_write_array (struct lcd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hx8357_spi_write_byte (struct lcd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx8369_seq_display_related ; 
 int /*<<< orphan*/  hx8369_seq_extension_command ; 
 int /*<<< orphan*/  hx8369_seq_gamma_curve_related ; 
 int /*<<< orphan*/  hx8369_seq_gip ; 
 int /*<<< orphan*/  hx8369_seq_panel_waveform_cycle ; 
 int /*<<< orphan*/  hx8369_seq_power ; 
 int /*<<< orphan*/  hx8369_seq_set_address_mode ; 
 int /*<<< orphan*/  hx8369_seq_set_display_brightness ; 
 int /*<<< orphan*/  hx8369_seq_vcom ; 
 int /*<<< orphan*/  hx8369_seq_write_CABC_control ; 
 int /*<<< orphan*/  hx8369_seq_write_CABC_control_setting ; 
 int /*<<< orphan*/  hx8369_seq_write_CABC_min_brightness ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hx8369_lcd_init(struct lcd_device *lcdev)
{
	int ret;

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_extension_command,
				ARRAY_SIZE(hx8369_seq_extension_command));
	if (ret < 0)
		return ret;
	usleep_range(10000, 12000);

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_display_related,
				ARRAY_SIZE(hx8369_seq_display_related));
	if (ret < 0)
		return ret;

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_panel_waveform_cycle,
				ARRAY_SIZE(hx8369_seq_panel_waveform_cycle));
	if (ret < 0)
		return ret;

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_set_address_mode,
				ARRAY_SIZE(hx8369_seq_set_address_mode));
	if (ret < 0)
		return ret;

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_vcom,
				ARRAY_SIZE(hx8369_seq_vcom));
	if (ret < 0)
		return ret;

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_gip,
				ARRAY_SIZE(hx8369_seq_gip));
	if (ret < 0)
		return ret;

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_power,
				ARRAY_SIZE(hx8369_seq_power));
	if (ret < 0)
		return ret;

	ret = hx8357_spi_write_byte(lcdev, HX8357_EXIT_SLEEP_MODE);
	if (ret < 0)
		return ret;

	/*
	 * The controller needs 120ms to fully recover from exiting sleep mode
	 */
	msleep(120);

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_gamma_curve_related,
				ARRAY_SIZE(hx8369_seq_gamma_curve_related));
	if (ret < 0)
		return ret;

	ret = hx8357_spi_write_byte(lcdev, HX8357_EXIT_SLEEP_MODE);
	if (ret < 0)
		return ret;
	usleep_range(1000, 1200);

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_write_CABC_control,
				ARRAY_SIZE(hx8369_seq_write_CABC_control));
	if (ret < 0)
		return ret;
	usleep_range(10000, 12000);

	ret = hx8357_spi_write_array(lcdev,
			hx8369_seq_write_CABC_control_setting,
			ARRAY_SIZE(hx8369_seq_write_CABC_control_setting));
	if (ret < 0)
		return ret;

	ret = hx8357_spi_write_array(lcdev,
			hx8369_seq_write_CABC_min_brightness,
			ARRAY_SIZE(hx8369_seq_write_CABC_min_brightness));
	if (ret < 0)
		return ret;
	usleep_range(10000, 12000);

	ret = hx8357_spi_write_array(lcdev, hx8369_seq_set_display_brightness,
				ARRAY_SIZE(hx8369_seq_set_display_brightness));
	if (ret < 0)
		return ret;

	ret = hx8357_spi_write_byte(lcdev, HX8357_SET_DISPLAY_ON);
	if (ret < 0)
		return ret;

	return 0;
}