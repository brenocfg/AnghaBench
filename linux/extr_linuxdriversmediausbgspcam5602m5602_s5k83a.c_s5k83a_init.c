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
typedef  int u8 ;
struct sd {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
#define  BRIDGE 130 
 int EINVAL ; 
#define  SENSOR 129 
#define  SENSOR_LONG 128 
 scalar_t__ dump_sensor ; 
 int** init_s5k83a ; 
 int m5602_write_bridge (struct sd*,int,int) ; 
 int m5602_write_sensor (struct sd*,int,int*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  s5k83a_dump_registers (struct sd*) ; 

int s5k83a_init(struct sd *sd)
{
	int i, err = 0;

	for (i = 0; i < ARRAY_SIZE(init_s5k83a) && !err; i++) {
		u8 data[2] = {0x00, 0x00};

		switch (init_s5k83a[i][0]) {
		case BRIDGE:
			err = m5602_write_bridge(sd,
					init_s5k83a[i][1],
					init_s5k83a[i][2]);
			break;

		case SENSOR:
			data[0] = init_s5k83a[i][2];
			err = m5602_write_sensor(sd,
				init_s5k83a[i][1], data, 1);
			break;

		case SENSOR_LONG:
			data[0] = init_s5k83a[i][2];
			data[1] = init_s5k83a[i][3];
			err = m5602_write_sensor(sd,
				init_s5k83a[i][1], data, 2);
			break;
		default:
			pr_info("Invalid stream command, exiting init\n");
			return -EINVAL;
		}
	}

	if (dump_sensor)
		s5k83a_dump_registers(sd);

	return err;
}