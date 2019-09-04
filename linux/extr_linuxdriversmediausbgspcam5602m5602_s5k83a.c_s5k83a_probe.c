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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__** cam_mode; int nmodes; } ;
struct TYPE_5__ {TYPE_1__ cam; } ;
struct sd {int /*<<< orphan*/ * rotation_thread; TYPE_2__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 int /*<<< orphan*/  D_PROBE ; 
 int ENODEV ; 
 scalar_t__ S5K83A_SENSOR ; 
 scalar_t__ SENSOR ; 
 scalar_t__ force_sensor ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ m5602_read_sensor (struct sd*,int,scalar_t__*,int) ; 
 int m5602_write_bridge (struct sd*,scalar_t__,scalar_t__) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__** preinit_s5k83a ; 
 TYPE_3__ s5k83a ; 
 scalar_t__** s5k83a_modes ; 

int s5k83a_probe(struct sd *sd)
{
	u8 prod_id = 0, ver_id = 0;
	int i, err = 0;
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;

	if (force_sensor) {
		if (force_sensor == S5K83A_SENSOR) {
			pr_info("Forcing a %s sensor\n", s5k83a.name);
			goto sensor_found;
		}
		/* If we want to force another sensor, don't try to probe this
		 * one */
		return -ENODEV;
	}

	gspca_dbg(gspca_dev, D_PROBE, "Probing for a s5k83a sensor\n");

	/* Preinit the sensor */
	for (i = 0; i < ARRAY_SIZE(preinit_s5k83a) && !err; i++) {
		u8 data[2] = {preinit_s5k83a[i][2], preinit_s5k83a[i][3]};
		if (preinit_s5k83a[i][0] == SENSOR)
			err = m5602_write_sensor(sd, preinit_s5k83a[i][1],
				data, 2);
		else
			err = m5602_write_bridge(sd, preinit_s5k83a[i][1],
				data[0]);
	}

	/* We don't know what register (if any) that contain the product id
	 * Just pick the first addresses that seem to produce the same results
	 * on multiple machines */
	if (m5602_read_sensor(sd, 0x00, &prod_id, 1))
		return -ENODEV;

	if (m5602_read_sensor(sd, 0x01, &ver_id, 1))
		return -ENODEV;

	if ((prod_id == 0xff) || (ver_id == 0xff))
		return -ENODEV;
	else
		pr_info("Detected a s5k83a sensor\n");

sensor_found:
	sd->gspca_dev.cam.cam_mode = s5k83a_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(s5k83a_modes);

	/* null the pointer! thread is't running now */
	sd->rotation_thread = NULL;

	return 0;
}