#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct st_lsm6dsx_sensor {size_t id; TYPE_3__* hw; } ;
struct st_lsm6dsx_odr_table_entry {TYPE_1__* odr_avl; } ;
struct TYPE_6__ {TYPE_2__* settings; } ;
struct TYPE_5__ {struct st_lsm6dsx_odr_table_entry* odr_table; } ;
struct TYPE_4__ {scalar_t__ hz; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
 int ST_LSM6DSX_ODR_LIST_SIZE ; 

int st_lsm6dsx_check_odr(struct st_lsm6dsx_sensor *sensor, u16 odr, u8 *val)
{
	const struct st_lsm6dsx_odr_table_entry *odr_table;
	int i;

	odr_table = &sensor->hw->settings->odr_table[sensor->id];
	for (i = 0; i < ST_LSM6DSX_ODR_LIST_SIZE; i++)
		/*
		 * ext devices can run at different odr respect to
		 * accel sensor
		 */
		if (odr_table->odr_avl[i].hz >= odr)
			break;

	if (i == ST_LSM6DSX_ODR_LIST_SIZE)
		return -EINVAL;

	*val = odr_table->odr_avl[i].val;

	return 0;
}