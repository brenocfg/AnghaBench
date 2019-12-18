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
 int PEX_SENSOR_TYPE_LEN ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  temp_sensor_sig ; 

__attribute__((used)) static int is_temp_sensor(const char *sensor_id, int len)
{
	if (len < PEX_SENSOR_TYPE_LEN)
		return 0;

	if (!memcmp(sensor_id, temp_sensor_sig, PEX_SENSOR_TYPE_LEN))
		return 1;
	return 0;
}