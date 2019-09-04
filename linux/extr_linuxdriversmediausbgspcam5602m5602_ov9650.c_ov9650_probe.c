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
typedef  size_t u8 ;
struct TYPE_4__ {scalar_t__** cam_mode; size_t nmodes; } ;
struct TYPE_5__ {TYPE_1__ cam; } ;
struct sd {TYPE_2__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__**) ; 
 int /*<<< orphan*/  D_PROBE ; 
 int ENODEV ; 
 int /*<<< orphan*/  OV9650_PID ; 
 scalar_t__ OV9650_SENSOR ; 
 int /*<<< orphan*/  OV9650_VER ; 
 scalar_t__ SENSOR ; 
 scalar_t__ force_sensor ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ m5602_read_sensor (struct sd*,int /*<<< orphan*/ ,size_t*,int) ; 
 int m5602_write_bridge (struct sd*,scalar_t__,size_t) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,size_t*,int) ; 
 TYPE_3__ ov9650 ; 
 scalar_t__** ov9650_modes ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__** preinit_ov9650 ; 

int ov9650_probe(struct sd *sd)
{
	int err = 0;
	u8 prod_id = 0, ver_id = 0, i;
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;

	if (force_sensor) {
		if (force_sensor == OV9650_SENSOR) {
			pr_info("Forcing an %s sensor\n", ov9650.name);
			goto sensor_found;
		}
		/* If we want to force another sensor,
		   don't try to probe this one */
		return -ENODEV;
	}

	gspca_dbg(gspca_dev, D_PROBE, "Probing for an ov9650 sensor\n");

	/* Run the pre-init before probing the sensor */
	for (i = 0; i < ARRAY_SIZE(preinit_ov9650) && !err; i++) {
		u8 data = preinit_ov9650[i][2];
		if (preinit_ov9650[i][0] == SENSOR)
			err = m5602_write_sensor(sd,
				preinit_ov9650[i][1], &data, 1);
		else
			err = m5602_write_bridge(sd,
				preinit_ov9650[i][1], data);
	}

	if (err < 0)
		return err;

	if (m5602_read_sensor(sd, OV9650_PID, &prod_id, 1))
		return -ENODEV;

	if (m5602_read_sensor(sd, OV9650_VER, &ver_id, 1))
		return -ENODEV;

	if ((prod_id == 0x96) && (ver_id == 0x52)) {
		pr_info("Detected an ov9650 sensor\n");
		goto sensor_found;
	}
	return -ENODEV;

sensor_found:
	sd->gspca_dev.cam.cam_mode = ov9650_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(ov9650_modes);

	return 0;
}