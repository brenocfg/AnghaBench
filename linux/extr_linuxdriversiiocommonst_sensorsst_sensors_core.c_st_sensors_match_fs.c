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
struct TYPE_4__ {TYPE_1__* fs_avl; } ;
struct st_sensor_settings {TYPE_2__ fs; } ;
struct TYPE_3__ {unsigned int num; } ;

/* Variables and functions */
 int EINVAL ; 
 int ST_SENSORS_FULLSCALE_AVL_MAX ; 

__attribute__((used)) static int st_sensors_match_fs(struct st_sensor_settings *sensor_settings,
					unsigned int fs, int *index_fs_avl)
{
	int i, ret = -EINVAL;

	for (i = 0; i < ST_SENSORS_FULLSCALE_AVL_MAX; i++) {
		if (sensor_settings->fs.fs_avl[i].num == 0)
			goto st_sensors_match_odr_error;

		if (sensor_settings->fs.fs_avl[i].num == fs) {
			*index_fs_avl = i;
			ret = 0;
			break;
		}
	}

st_sensors_match_odr_error:
	return ret;
}