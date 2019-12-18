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
typedef  int u8 ;
struct TYPE_4__ {scalar_t__** cam_mode; int nmodes; } ;
struct TYPE_5__ {TYPE_1__ cam; } ;
struct sd {TYPE_2__ gspca_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 scalar_t__ BRIDGE ; 
 int ENODEV ; 
 int /*<<< orphan*/  OV7660_PID ; 
 scalar_t__ OV7660_SENSOR ; 
 int /*<<< orphan*/  OV7660_VER ; 
 scalar_t__ force_sensor ; 
 scalar_t__ m5602_read_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 
 int m5602_write_bridge (struct sd*,scalar_t__,scalar_t__) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,int*,int) ; 
 TYPE_3__ ov7660 ; 
 scalar_t__** ov7660_modes ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__** preinit_ov7660 ; 

int ov7660_probe(struct sd *sd)
{
	int err = 0, i;
	u8 prod_id = 0, ver_id = 0;

	if (force_sensor) {
		if (force_sensor == OV7660_SENSOR) {
			pr_info("Forcing an %s sensor\n", ov7660.name);
			goto sensor_found;
		}
		/* If we want to force another sensor,
		don't try to probe this one */
		return -ENODEV;
	}

	/* Do the preinit */
	for (i = 0; i < ARRAY_SIZE(preinit_ov7660) && !err; i++) {
		u8 data[2];

		if (preinit_ov7660[i][0] == BRIDGE) {
			err = m5602_write_bridge(sd,
				preinit_ov7660[i][1],
				preinit_ov7660[i][2]);
		} else {
			data[0] = preinit_ov7660[i][2];
			err = m5602_write_sensor(sd,
				preinit_ov7660[i][1], data, 1);
		}
	}
	if (err < 0)
		return err;

	if (m5602_read_sensor(sd, OV7660_PID, &prod_id, 1))
		return -ENODEV;

	if (m5602_read_sensor(sd, OV7660_VER, &ver_id, 1))
		return -ENODEV;

	pr_info("Sensor reported 0x%x%x\n", prod_id, ver_id);

	if ((prod_id == 0x76) && (ver_id == 0x60)) {
		pr_info("Detected a ov7660 sensor\n");
		goto sensor_found;
	}
	return -ENODEV;

sensor_found:
	sd->gspca_dev.cam.cam_mode = ov7660_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(ov7660_modes);

	return 0;
}