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
struct ibmpex_bmc_data {int sensor_major; } ;

/* Variables and functions */
 int /*<<< orphan*/  PEX_MULT_LEN ; 
 int PEX_SENSOR_TYPE_LEN ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watt_sensor_sig ; 

__attribute__((used)) static int power_sensor_multiplier(struct ibmpex_bmc_data *data,
				   const char *sensor_id, int len)
{
	int i;

	if (data->sensor_major == 2)
		return 1000000;

	for (i = PEX_SENSOR_TYPE_LEN; i < len - 1; i++)
		if (!memcmp(&sensor_id[i], watt_sensor_sig, PEX_MULT_LEN))
			return 1000000;

	return 100000;
}