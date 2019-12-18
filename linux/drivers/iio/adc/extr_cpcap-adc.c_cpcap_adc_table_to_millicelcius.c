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

/* Variables and functions */
 int CPCAP_MAX_TEMP_LVL ; 
 unsigned short** temp_map ; 

__attribute__((used)) static int cpcap_adc_table_to_millicelcius(unsigned short value)
{
	int i, result = 0, alpha;

	if (value <= temp_map[CPCAP_MAX_TEMP_LVL - 1][0])
		return temp_map[CPCAP_MAX_TEMP_LVL - 1][1];

	if (value >= temp_map[0][0])
		return temp_map[0][1];

	for (i = 0; i < CPCAP_MAX_TEMP_LVL - 1; i++) {
		if ((value <= temp_map[i][0]) &&
		    (value >= temp_map[i + 1][0])) {
			if (value == temp_map[i][0]) {
				result = temp_map[i][1];
			} else if (value == temp_map[i + 1][0]) {
				result = temp_map[i + 1][1];
			} else {
				alpha = ((value - temp_map[i][0]) * 1000) /
					(temp_map[i + 1][0] - temp_map[i][0]);

				result = temp_map[i][1] +
					((alpha * (temp_map[i + 1][1] -
						 temp_map[i][1])) / 1000);
			}
			break;
		}
	}

	return result;
}