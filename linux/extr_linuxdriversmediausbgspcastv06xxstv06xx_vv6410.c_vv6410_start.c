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
typedef  int u32 ;
struct cam {TYPE_1__* cam_mode; } ;
struct TYPE_4__ {size_t curr_mode; struct cam cam; } ;
struct sd {TYPE_2__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  D_STREAM ; 
 int LED_ON ; 
 int /*<<< orphan*/  STV_LED_CTRL ; 
 int /*<<< orphan*/  STV_SCAN_RATE ; 
 int /*<<< orphan*/  STV_X_CTRL ; 
 int /*<<< orphan*/  STV_Y_CTRL ; 
 int /*<<< orphan*/  VV6410_SETUP0 ; 
 int VV6410_SUBSAMPLE ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int stv06xx_write_bridge (struct sd*,int /*<<< orphan*/ ,int) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vv6410_start(struct sd *sd)
{
	int err;
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	struct cam *cam = &sd->gspca_dev.cam;
	u32 priv = cam->cam_mode[sd->gspca_dev.curr_mode].priv;

	if (priv & VV6410_SUBSAMPLE) {
		gspca_dbg(gspca_dev, D_CONF, "Enabling subsampling\n");
		stv06xx_write_bridge(sd, STV_Y_CTRL, 0x02);
		stv06xx_write_bridge(sd, STV_X_CTRL, 0x06);

		stv06xx_write_bridge(sd, STV_SCAN_RATE, 0x10);
	} else {
		stv06xx_write_bridge(sd, STV_Y_CTRL, 0x01);
		stv06xx_write_bridge(sd, STV_X_CTRL, 0x0a);
		stv06xx_write_bridge(sd, STV_SCAN_RATE, 0x00);

	}

	/* Turn on LED */
	err = stv06xx_write_bridge(sd, STV_LED_CTRL, LED_ON);
	if (err < 0)
		return err;

	err = stv06xx_write_sensor(sd, VV6410_SETUP0, 0);
	if (err < 0)
		return err;

	gspca_dbg(gspca_dev, D_STREAM, "Starting stream\n");

	return 0;
}