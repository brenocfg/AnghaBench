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
typedef  int u8 ;
struct hidpp_report {int dummy; } ;
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TOUCHPAD_SET_RAW_REPORT_STATE ; 
 int hidpp_send_fap_command_sync (struct hidpp_device*,int,int /*<<< orphan*/ ,int*,int,struct hidpp_report*) ; 

__attribute__((used)) static int hidpp_touchpad_set_raw_report_state(struct hidpp_device *hidpp_dev,
		u8 feature_index, bool send_raw_reports,
		bool sensor_enhanced_settings)
{
	struct hidpp_report response;

	/*
	 * Params:
	 *   bit 0 - enable raw
	 *   bit 1 - 16bit Z, no area
	 *   bit 2 - enhanced sensitivity
	 *   bit 3 - width, height (4 bits each) instead of area
	 *   bit 4 - send raw + gestures (degrades smoothness)
	 *   remaining bits - reserved
	 */
	u8 params = send_raw_reports | (sensor_enhanced_settings << 2);

	return hidpp_send_fap_command_sync(hidpp_dev, feature_index,
		CMD_TOUCHPAD_SET_RAW_REPORT_STATE, &params, 1, &response);
}