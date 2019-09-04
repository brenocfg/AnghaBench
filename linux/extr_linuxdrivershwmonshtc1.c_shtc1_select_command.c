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
struct TYPE_2__ {scalar_t__ blocking_io; scalar_t__ high_precision; } ;
struct shtc1_data {int /*<<< orphan*/  nonblocking_wait_time; TYPE_1__ setup; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHTC1_NONBLOCKING_WAIT_TIME_HPM ; 
 int /*<<< orphan*/  SHTC1_NONBLOCKING_WAIT_TIME_LPM ; 
 int /*<<< orphan*/  shtc1_cmd_measure_blocking_hpm ; 
 int /*<<< orphan*/  shtc1_cmd_measure_blocking_lpm ; 
 int /*<<< orphan*/  shtc1_cmd_measure_nonblocking_hpm ; 
 int /*<<< orphan*/  shtc1_cmd_measure_nonblocking_lpm ; 

__attribute__((used)) static void shtc1_select_command(struct shtc1_data *data)
{
	if (data->setup.high_precision) {
		data->command = data->setup.blocking_io ?
				shtc1_cmd_measure_blocking_hpm :
				shtc1_cmd_measure_nonblocking_hpm;
		data->nonblocking_wait_time = SHTC1_NONBLOCKING_WAIT_TIME_HPM;

	} else {
		data->command = data->setup.blocking_io ?
				shtc1_cmd_measure_blocking_lpm :
				shtc1_cmd_measure_nonblocking_lpm;
		data->nonblocking_wait_time = SHTC1_NONBLOCKING_WAIT_TIME_LPM;
	}
}