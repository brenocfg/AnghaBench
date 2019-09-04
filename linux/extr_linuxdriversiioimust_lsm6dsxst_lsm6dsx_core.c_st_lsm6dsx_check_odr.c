#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct st_lsm6dsx_sensor {size_t id; } ;
struct TYPE_4__ {TYPE_1__* odr_avl; } ;
struct TYPE_3__ {scalar_t__ hz; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
 int ST_LSM6DSX_ODR_LIST_SIZE ; 
 TYPE_2__* st_lsm6dsx_odr_table ; 

__attribute__((used)) static int st_lsm6dsx_check_odr(struct st_lsm6dsx_sensor *sensor, u16 odr,
				u8 *val)
{
	int i;

	for (i = 0; i < ST_LSM6DSX_ODR_LIST_SIZE; i++)
		if (st_lsm6dsx_odr_table[sensor->id].odr_avl[i].hz == odr)
			break;

	if (i == ST_LSM6DSX_ODR_LIST_SIZE)
		return -EINVAL;

	*val = st_lsm6dsx_odr_table[sensor->id].odr_avl[i].val;

	return 0;
}