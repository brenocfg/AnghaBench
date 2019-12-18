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
struct abituguru_data {int pwms; int** pwm_settings; int* bank1_sensors; int** bank1_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABIT_UGURU_DEBUG (int,char*,...) ; 
 scalar_t__ ABIT_UGURU_MAX_PWMS ; 
 size_t ABIT_UGURU_TEMP_SENSOR ; 
 int* abituguru_pwm_max ; 
 int* abituguru_pwm_min ; 
 scalar_t__ pwms ; 

__attribute__((used)) static void
abituguru_detect_no_pwms(struct abituguru_data *data)
{
	int i, j;

	if (pwms > 0 && pwms <= ABIT_UGURU_MAX_PWMS) {
		data->pwms = pwms;
		ABIT_UGURU_DEBUG(2, "assuming %d PWM outputs because of "
			"\"pwms\" module param\n", (int)data->pwms);
		return;
	}

	ABIT_UGURU_DEBUG(2, "detecting number of PWM outputs\n");
	for (i = 0; i < ABIT_UGURU_MAX_PWMS; i++) {
		/*
		 * 0x80 is the enable bit and the low
		 * nibble is which temp sensor to use,
		 * the other bits should be 0
		 */
		if (data->pwm_settings[i][0] & ~0x8F) {
			ABIT_UGURU_DEBUG(2, "  pwm channel %d does not seem "
				"to be a pwm channel: settings[0] = %02X\n",
				i, (unsigned int)data->pwm_settings[i][0]);
			break;
		}

		/*
		 * the low nibble must correspond to one of the temp sensors
		 * we've found
		 */
		for (j = 0; j < data->bank1_sensors[ABIT_UGURU_TEMP_SENSOR];
				j++) {
			if (data->bank1_address[ABIT_UGURU_TEMP_SENSOR][j] ==
					(data->pwm_settings[i][0] & 0x0F))
				break;
		}
		if (j == data->bank1_sensors[ABIT_UGURU_TEMP_SENSOR]) {
			ABIT_UGURU_DEBUG(2, "  pwm channel %d does not seem "
				"to be a pwm channel: %d is not a valid temp "
				"sensor address\n", i,
				data->pwm_settings[i][0] & 0x0F);
			break;
		}

		/* check if all other settings are within the allowed range */
		for (j = 1; j < 5; j++) {
			u8 min;
			/* special case pwm1 min pwm% */
			if ((i == 0) && ((j == 1) || (j == 2)))
				min = 77;
			else
				min = abituguru_pwm_min[j];
			if (data->pwm_settings[i][j] < min) {
				ABIT_UGURU_DEBUG(2, "  pwm channel %d does "
					"not seem to be a pwm channel: "
					"setting %d (%d) is below the minimum "
					"value (%d)\n", i, j,
					(int)data->pwm_settings[i][j],
					(int)min);
				goto abituguru_detect_no_pwms_exit;
			}
			if (data->pwm_settings[i][j] > abituguru_pwm_max[j]) {
				ABIT_UGURU_DEBUG(2, "  pwm channel %d does "
					"not seem to be a pwm channel: "
					"setting %d (%d) is above the maximum "
					"value (%d)\n", i, j,
					(int)data->pwm_settings[i][j],
					(int)abituguru_pwm_max[j]);
				goto abituguru_detect_no_pwms_exit;
			}
		}

		/* check that min temp < max temp and min pwm < max pwm */
		if (data->pwm_settings[i][1] >= data->pwm_settings[i][2]) {
			ABIT_UGURU_DEBUG(2, "  pwm channel %d does not seem "
				"to be a pwm channel: min pwm (%d) >= "
				"max pwm (%d)\n", i,
				(int)data->pwm_settings[i][1],
				(int)data->pwm_settings[i][2]);
			break;
		}
		if (data->pwm_settings[i][3] >= data->pwm_settings[i][4]) {
			ABIT_UGURU_DEBUG(2, "  pwm channel %d does not seem "
				"to be a pwm channel: min temp (%d) >= "
				"max temp (%d)\n", i,
				(int)data->pwm_settings[i][3],
				(int)data->pwm_settings[i][4]);
			break;
		}
	}

abituguru_detect_no_pwms_exit:
	data->pwms = i;
	ABIT_UGURU_DEBUG(2, " found: %d PWM outputs\n", (int)data->pwms);
}