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
typedef  scalar_t__ u8 ;
struct sd {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 scalar_t__ BRIDGE ; 
 scalar_t__ dump_sensor ; 
 scalar_t__** init_ov7660 ; 
 int m5602_write_bridge (struct sd*,scalar_t__,scalar_t__) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  ov7660_dump_registers (struct sd*) ; 

int ov7660_init(struct sd *sd)
{
	int i, err;

	/* Init the sensor */
	for (i = 0; i < ARRAY_SIZE(init_ov7660); i++) {
		u8 data[2];

		if (init_ov7660[i][0] == BRIDGE) {
			err = m5602_write_bridge(sd,
				init_ov7660[i][1],
				init_ov7660[i][2]);
		} else {
			data[0] = init_ov7660[i][2];
			err = m5602_write_sensor(sd,
				init_ov7660[i][1], data, 1);
		}
		if (err < 0)
			return err;
	}

	if (dump_sensor)
		ov7660_dump_registers(sd);

	return 0;
}