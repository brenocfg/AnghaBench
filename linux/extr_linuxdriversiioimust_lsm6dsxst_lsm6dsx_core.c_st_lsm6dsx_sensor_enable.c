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
struct st_lsm6dsx_sensor {int /*<<< orphan*/  id; TYPE_1__* hw; int /*<<< orphan*/  odr; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_set_odr (struct st_lsm6dsx_sensor*,int /*<<< orphan*/ ) ; 

int st_lsm6dsx_sensor_enable(struct st_lsm6dsx_sensor *sensor)
{
	int err;

	err = st_lsm6dsx_set_odr(sensor, sensor->odr);
	if (err < 0)
		return err;

	sensor->hw->enable_mask |= BIT(sensor->id);

	return 0;
}