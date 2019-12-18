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
typedef  int u8 ;
struct sd {TYPE_2__* vflip; TYPE_1__* hflip; } ;
struct gspca_dev {scalar_t__ streaming; } ;
struct TYPE_4__ {int val; } ;
struct TYPE_3__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  OV9650_MVFP ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ov9650_flip_dmi_table ; 
 int ov9650_start (struct sd*) ; 

__attribute__((used)) static int ov9650_set_hvflip(struct gspca_dev *gspca_dev)
{
	int err;
	u8 i2c_data;
	struct sd *sd = (struct sd *) gspca_dev;
	int hflip = sd->hflip->val;
	int vflip = sd->vflip->val;

	gspca_dbg(gspca_dev, D_CONF, "Set hvflip to %d %d\n", hflip, vflip);

	if (dmi_check_system(ov9650_flip_dmi_table))
		vflip = !vflip;

	i2c_data = (hflip << 5) | (vflip << 4);
	err = m5602_write_sensor(sd, OV9650_MVFP, &i2c_data, 1);
	if (err < 0)
		return err;

	/* When vflip is toggled we need to readjust the bridge hsync/vsync */
	if (gspca_dev->streaming)
		err = ov9650_start(sd);

	return err;
}