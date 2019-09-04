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
struct abituguru_data {int bank2_sensors; int** bank2_settings; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABIT_UGURU_DEBUG (int,char*,...) ; 
 scalar_t__ ABIT_UGURU_MAX_BANK2_SENSORS ; 
 int abituguru_bank2_max_threshold ; 
 int abituguru_bank2_min_threshold ; 
 scalar_t__ fan_sensors ; 

__attribute__((used)) static void
abituguru_detect_no_bank2_sensors(struct abituguru_data *data)
{
	int i;

	if (fan_sensors > 0 && fan_sensors <= ABIT_UGURU_MAX_BANK2_SENSORS) {
		data->bank2_sensors = fan_sensors;
		ABIT_UGURU_DEBUG(2, "assuming %d fan sensors because of "
			"\"fan_sensors\" module param\n",
			(int)data->bank2_sensors);
		return;
	}

	ABIT_UGURU_DEBUG(2, "detecting number of fan sensors\n");
	for (i = 0; i < ABIT_UGURU_MAX_BANK2_SENSORS; i++) {
		/*
		 * 0x89 are the known used bits:
		 * -0x80 enable shutdown
		 * -0x08 enable beep
		 * -0x01 enable alarm
		 * All other bits should be 0, but on some motherboards
		 * 0x40 (bit 6) is also high for some of the fans??
		 */
		if (data->bank2_settings[i][0] & ~0xC9) {
			ABIT_UGURU_DEBUG(2, "  bank2 sensor %d does not seem "
				"to be a fan sensor: settings[0] = %02X\n",
				i, (unsigned int)data->bank2_settings[i][0]);
			break;
		}

		/* check if the threshold is within the allowed range */
		if (data->bank2_settings[i][1] <
				abituguru_bank2_min_threshold) {
			ABIT_UGURU_DEBUG(2, "  bank2 sensor %d does not seem "
				"to be a fan sensor: the threshold (%d) is "
				"below the minimum (%d)\n", i,
				(int)data->bank2_settings[i][1],
				(int)abituguru_bank2_min_threshold);
			break;
		}
		if (data->bank2_settings[i][1] >
				abituguru_bank2_max_threshold) {
			ABIT_UGURU_DEBUG(2, "  bank2 sensor %d does not seem "
				"to be a fan sensor: the threshold (%d) is "
				"above the maximum (%d)\n", i,
				(int)data->bank2_settings[i][1],
				(int)abituguru_bank2_max_threshold);
			break;
		}
	}

	data->bank2_sensors = i;
	ABIT_UGURU_DEBUG(2, " found: %d fan sensors\n",
		(int)data->bank2_sensors);
}