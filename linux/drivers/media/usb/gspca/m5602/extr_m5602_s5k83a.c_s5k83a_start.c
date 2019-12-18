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
struct sd {int /*<<< orphan*/ * rotation_thread; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SENSOR ; 
 int /*<<< orphan*/ * kthread_create (int /*<<< orphan*/ ,struct sd*,char*) ; 
 int m5602_write_bridge (struct sd*,scalar_t__,scalar_t__) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  rotation_thread_function ; 
 int s5k83a_set_led_indication (struct sd*,int) ; 
 scalar_t__** start_s5k83a ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ *) ; 

int s5k83a_start(struct sd *sd)
{
	int i, err = 0;

	/* Create another thread, polling the GPIO ports of the camera to check
	   if it got rotated. This is how the windows driver does it so we have
	   to assume that there is no better way of accomplishing this */
	sd->rotation_thread = kthread_create(rotation_thread_function,
					     sd, "rotation thread");
	if (IS_ERR(sd->rotation_thread)) {
		err = PTR_ERR(sd->rotation_thread);
		sd->rotation_thread = NULL;
		return err;
	}
	wake_up_process(sd->rotation_thread);

	/* Preinit the sensor */
	for (i = 0; i < ARRAY_SIZE(start_s5k83a) && !err; i++) {
		u8 data[2] = {start_s5k83a[i][2], start_s5k83a[i][3]};
		if (start_s5k83a[i][0] == SENSOR)
			err = m5602_write_sensor(sd, start_s5k83a[i][1],
				data, 2);
		else
			err = m5602_write_bridge(sd, start_s5k83a[i][1],
				data[0]);
	}
	if (err < 0)
		return err;

	return s5k83a_set_led_indication(sd, 1);
}