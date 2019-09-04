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
struct cam {TYPE_1__* cam_mode; } ;
struct TYPE_4__ {size_t curr_mode; struct cam cam; } ;
struct sd {TYPE_2__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_3__ {int width; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
#define  BRIDGE 130 
 int /*<<< orphan*/  D_CONF ; 
 int EINVAL ; 
#define  SENSOR 129 
#define  SENSOR_LONG 128 
 int /*<<< orphan*/ ** SXGA_s5k4aa ; 
 int /*<<< orphan*/ ** VGA_s5k4aa ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int m5602_write_bridge (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int s5k4aa_start(struct sd *sd)
{
	int i, err = 0;
	u8 data[2];
	struct cam *cam = &sd->gspca_dev.cam;
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;

	switch (cam->cam_mode[sd->gspca_dev.curr_mode].width) {
	case 1280:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for SXGA mode\n");

		for (i = 0; i < ARRAY_SIZE(SXGA_s5k4aa); i++) {
			switch (SXGA_s5k4aa[i][0]) {
			case BRIDGE:
				err = m5602_write_bridge(sd,
						 SXGA_s5k4aa[i][1],
						 SXGA_s5k4aa[i][2]);
			break;

			case SENSOR:
				data[0] = SXGA_s5k4aa[i][2];
				err = m5602_write_sensor(sd,
						 SXGA_s5k4aa[i][1],
						 data, 1);
			break;

			case SENSOR_LONG:
				data[0] = SXGA_s5k4aa[i][2];
				data[1] = SXGA_s5k4aa[i][3];
				err = m5602_write_sensor(sd,
						  SXGA_s5k4aa[i][1],
						  data, 2);
			break;

			default:
				pr_err("Invalid stream command, exiting init\n");
				return -EINVAL;
			}
		}
		break;

	case 640:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for VGA mode\n");

		for (i = 0; i < ARRAY_SIZE(VGA_s5k4aa); i++) {
			switch (VGA_s5k4aa[i][0]) {
			case BRIDGE:
				err = m5602_write_bridge(sd,
						 VGA_s5k4aa[i][1],
						 VGA_s5k4aa[i][2]);
			break;

			case SENSOR:
				data[0] = VGA_s5k4aa[i][2];
				err = m5602_write_sensor(sd,
						 VGA_s5k4aa[i][1],
						 data, 1);
			break;

			case SENSOR_LONG:
				data[0] = VGA_s5k4aa[i][2];
				data[1] = VGA_s5k4aa[i][3];
				err = m5602_write_sensor(sd,
						  VGA_s5k4aa[i][1],
						  data, 2);
			break;

			default:
				pr_err("Invalid stream command, exiting init\n");
				return -EINVAL;
			}
		}
		break;
	}
	if (err < 0)
		return err;

	return 0;
}