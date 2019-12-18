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
struct smiapp_sensor {scalar_t__* limits; } ;

/* Variables and functions */
 unsigned int SMIAPP_LIMIT_LAST ; 
 size_t SMIAPP_LIMIT_SCALER_N_MIN ; 
 int smiapp_get_limits (struct smiapp_sensor*,unsigned int*,int) ; 
 int /*<<< orphan*/  smiapp_replace_limit (struct smiapp_sensor*,size_t,int) ; 

__attribute__((used)) static int smiapp_get_all_limits(struct smiapp_sensor *sensor)
{
	unsigned int i;
	int rval;

	for (i = 0; i < SMIAPP_LIMIT_LAST; i++) {
		rval = smiapp_get_limits(sensor, &i, 1);
		if (rval < 0)
			return rval;
	}

	if (sensor->limits[SMIAPP_LIMIT_SCALER_N_MIN] == 0)
		smiapp_replace_limit(sensor, SMIAPP_LIMIT_SCALER_N_MIN, 16);

	return 0;
}