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
struct gspca_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 scalar_t__ BRIDGE ; 
 int /*<<< orphan*/  D_PROBE ; 
 int ENODEV ; 
 int /*<<< orphan*/  MT9M111_SC_CHIPVER ; 
 scalar_t__ MT9M111_SENSOR ; 
 scalar_t__ force_sensor ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ m5602_read_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 
 int m5602_write_bridge (struct sd*,scalar_t__,scalar_t__) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,int*,int) ; 
 TYPE_3__ mt9m111 ; 
 scalar_t__** mt9m111_modes ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__** preinit_mt9m111 ; 

int mt9m111_probe(struct sd *sd)
{
	u8 data[2] = {0x00, 0x00};
	int i, rc = 0;
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;

	if (force_sensor) {
		if (force_sensor == MT9M111_SENSOR) {
			pr_info("Forcing a %s sensor\n", mt9m111.name);
			goto sensor_found;
		}
		/* If we want to force another sensor, don't try to probe this
		 * one */
		return -ENODEV;
	}

	gspca_dbg(gspca_dev, D_PROBE, "Probing for a mt9m111 sensor\n");

	/* Do the preinit */
	for (i = 0; i < ARRAY_SIZE(preinit_mt9m111); i++) {
		if (preinit_mt9m111[i][0] == BRIDGE) {
			rc |= m5602_write_bridge(sd,
				preinit_mt9m111[i][1],
				preinit_mt9m111[i][2]);
		} else {
			data[0] = preinit_mt9m111[i][2];
			data[1] = preinit_mt9m111[i][3];
			rc |= m5602_write_sensor(sd,
				preinit_mt9m111[i][1], data, 2);
		}
	}
	if (rc < 0)
		return rc;

	if (m5602_read_sensor(sd, MT9M111_SC_CHIPVER, data, 2))
		return -ENODEV;

	if ((data[0] == 0x14) && (data[1] == 0x3a)) {
		pr_info("Detected a mt9m111 sensor\n");
		goto sensor_found;
	}

	return -ENODEV;

sensor_found:
	sd->gspca_dev.cam.cam_mode = mt9m111_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(mt9m111_modes);

	return 0;
}