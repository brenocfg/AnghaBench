#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ high_precision; scalar_t__ blocking_io; } ;
struct sht3x_data {scalar_t__ mode; scalar_t__ wait_time; int /*<<< orphan*/  command; TYPE_1__ setup; } ;

/* Variables and functions */
 scalar_t__ SHT3X_NONBLOCKING_WAIT_TIME_HPM ; 
 scalar_t__ SHT3X_NONBLOCKING_WAIT_TIME_LPM ; 
 int /*<<< orphan*/  sht3x_cmd_measure_blocking_hpm ; 
 int /*<<< orphan*/  sht3x_cmd_measure_blocking_lpm ; 
 int /*<<< orphan*/  sht3x_cmd_measure_nonblocking_hpm ; 
 int /*<<< orphan*/  sht3x_cmd_measure_nonblocking_lpm ; 
 int /*<<< orphan*/  sht3x_cmd_measure_periodic_mode ; 

__attribute__((used)) static void sht3x_select_command(struct sht3x_data *data)
{
	/*
	 * In blocking mode (clock stretching mode) the I2C bus
	 * is blocked for other traffic, thus the call to i2c_master_recv()
	 * will wait until the data is ready. For non blocking mode, we
	 * have to wait ourselves.
	 */
	if (data->mode > 0) {
		data->command = sht3x_cmd_measure_periodic_mode;
		data->wait_time = 0;
	} else if (data->setup.blocking_io) {
		data->command = data->setup.high_precision ?
				sht3x_cmd_measure_blocking_hpm :
				sht3x_cmd_measure_blocking_lpm;
		data->wait_time = 0;
	} else {
		if (data->setup.high_precision) {
			data->command = sht3x_cmd_measure_nonblocking_hpm;
			data->wait_time = SHT3X_NONBLOCKING_WAIT_TIME_HPM;
		} else {
			data->command = sht3x_cmd_measure_nonblocking_lpm;
			data->wait_time = SHT3X_NONBLOCKING_WAIT_TIME_LPM;
		}
	}
}