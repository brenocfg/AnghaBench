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
typedef  int /*<<< orphan*/  u8 ;
struct abx500_temp {struct ab8500_temp* plat_data; } ;
struct ab8500_temp {int /*<<< orphan*/  cfg; int /*<<< orphan*/  gpadc; int /*<<< orphan*/  btemp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAT_CTRL ; 
 int /*<<< orphan*/  BTEMP_BALL ; 
 int ab8500_btemp_get_batctrl_temp (int /*<<< orphan*/ ) ; 
 int ab8500_btemp_get_temp (int /*<<< orphan*/ ) ; 
 int ab8500_gpadc_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ab8500_voltage_to_temp (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int ab8500_read_sensor(struct abx500_temp *data, u8 sensor, int *temp)
{
	int voltage, ret;
	struct ab8500_temp *ab8500_data = data->plat_data;

	if (sensor == BAT_CTRL) {
		*temp = ab8500_btemp_get_batctrl_temp(ab8500_data->btemp);
	} else if (sensor == BTEMP_BALL) {
		*temp = ab8500_btemp_get_temp(ab8500_data->btemp);
	} else {
		voltage = ab8500_gpadc_convert(ab8500_data->gpadc, sensor);
		if (voltage < 0)
			return voltage;

		ret = ab8500_voltage_to_temp(&ab8500_data->cfg, voltage, temp);
		if (ret < 0)
			return ret;
	}

	return 0;
}