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
 int /*<<< orphan*/  PO1030_DEVID_H ; 
 scalar_t__ PO1030_SENSOR ; 
 scalar_t__ SENSOR ; 
 scalar_t__ force_sensor ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ m5602_read_sensor (struct sd*,int /*<<< orphan*/ ,size_t*,int) ; 
 int m5602_write_bridge (struct sd*,scalar_t__,size_t) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,size_t*,int) ; 
 TYPE_3__ po1030 ; 
 scalar_t__** po1030_modes ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__** preinit_po1030 ; 

int po1030_probe(struct sd *sd)
{
	int rc = 0;
	u8 dev_id_h = 0, i;
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;

	if (force_sensor) {
		if (force_sensor == PO1030_SENSOR) {
			pr_info("Forcing a %s sensor\n", po1030.name);
			goto sensor_found;
		}
		/* If we want to force another sensor, don't try to probe this
		 * one */
		return -ENODEV;
	}

	gspca_dbg(gspca_dev, D_PROBE, "Probing for a po1030 sensor\n");

	/* Run the pre-init to actually probe the unit */
	for (i = 0; i < ARRAY_SIZE(preinit_po1030); i++) {
		u8 data = preinit_po1030[i][2];
		if (preinit_po1030[i][0] == SENSOR)
			rc |= m5602_write_sensor(sd,
				preinit_po1030[i][1], &data, 1);
		else
			rc |= m5602_write_bridge(sd, preinit_po1030[i][1],
						data);
	}
	if (rc < 0)
		return rc;

	if (m5602_read_sensor(sd, PO1030_DEVID_H, &dev_id_h, 1))
		return -ENODEV;

	if (dev_id_h == 0x30) {
		pr_info("Detected a po1030 sensor\n");
		goto sensor_found;
	}
	return -ENODEV;

sensor_found:
	sd->gspca_dev.cam.cam_mode = po1030_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(po1030_modes);

	return 0;
}