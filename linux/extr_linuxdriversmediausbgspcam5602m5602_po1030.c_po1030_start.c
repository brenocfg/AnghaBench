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
struct cam {TYPE_1__* cam_mode; } ;
struct TYPE_4__ {size_t curr_mode; struct cam cam; } ;
struct sd {TYPE_2__ gspca_dev; } ;
struct TYPE_3__ {int width; int height; int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  M5602_XB_HSYNC_PARA ; 
 int /*<<< orphan*/  M5602_XB_LINE_OF_FRAME_H ; 
 int /*<<< orphan*/  M5602_XB_PIX_OF_LINE_H ; 
 int /*<<< orphan*/  M5602_XB_SENSOR_TYPE ; 
 int /*<<< orphan*/  M5602_XB_SIG_INI ; 
 int /*<<< orphan*/  M5602_XB_VSYNC_PARA ; 
 int /*<<< orphan*/  PO1030_CONTROL3 ; 
 int PO1030_SUBSAMPLING ; 
 int /*<<< orphan*/  PO1030_WINDOWHEIGHT_H ; 
 int /*<<< orphan*/  PO1030_WINDOWHEIGHT_L ; 
 int /*<<< orphan*/  PO1030_WINDOWWIDTH_H ; 
 int /*<<< orphan*/  PO1030_WINDOWWIDTH_L ; 
 int m5602_write_bridge (struct sd*,int /*<<< orphan*/ ,int) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

int po1030_start(struct sd *sd)
{
	struct cam *cam = &sd->gspca_dev.cam;
	int i, err = 0;
	int width = cam->cam_mode[sd->gspca_dev.curr_mode].width;
	int height = cam->cam_mode[sd->gspca_dev.curr_mode].height;
	int ver_offs = cam->cam_mode[sd->gspca_dev.curr_mode].priv;
	u8 data;

	switch (width) {
	case 320:
		data = PO1030_SUBSAMPLING;
		err = m5602_write_sensor(sd, PO1030_CONTROL3, &data, 1);
		if (err < 0)
			return err;

		data = ((width + 3) >> 8) & 0xff;
		err = m5602_write_sensor(sd, PO1030_WINDOWWIDTH_H, &data, 1);
		if (err < 0)
			return err;

		data = (width + 3) & 0xff;
		err = m5602_write_sensor(sd, PO1030_WINDOWWIDTH_L, &data, 1);
		if (err < 0)
			return err;

		data = ((height + 1) >> 8) & 0xff;
		err = m5602_write_sensor(sd, PO1030_WINDOWHEIGHT_H, &data, 1);
		if (err < 0)
			return err;

		data = (height + 1) & 0xff;
		err = m5602_write_sensor(sd, PO1030_WINDOWHEIGHT_L, &data, 1);

		height += 6;
		width -= 1;
		break;

	case 640:
		data = 0;
		err = m5602_write_sensor(sd, PO1030_CONTROL3, &data, 1);
		if (err < 0)
			return err;

		data = ((width + 7) >> 8) & 0xff;
		err = m5602_write_sensor(sd, PO1030_WINDOWWIDTH_H, &data, 1);
		if (err < 0)
			return err;

		data = (width + 7) & 0xff;
		err = m5602_write_sensor(sd, PO1030_WINDOWWIDTH_L, &data, 1);
		if (err < 0)
			return err;

		data = ((height + 3) >> 8) & 0xff;
		err = m5602_write_sensor(sd, PO1030_WINDOWHEIGHT_H, &data, 1);
		if (err < 0)
			return err;

		data = (height + 3) & 0xff;
		err = m5602_write_sensor(sd, PO1030_WINDOWHEIGHT_L, &data, 1);

		height += 12;
		width -= 2;
		break;
	}
	err = m5602_write_bridge(sd, M5602_XB_SENSOR_TYPE, 0x0c);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_LINE_OF_FRAME_H, 0x81);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_PIX_OF_LINE_H, 0x82);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_SIG_INI, 0x01);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA,
				 ((ver_offs >> 8) & 0xff));
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, (ver_offs & 0xff));
	if (err < 0)
		return err;

	for (i = 0; i < 2 && !err; i++)
		err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, 0);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, (height >> 8) & 0xff);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, (height & 0xff));
	if (err < 0)
		return err;

	for (i = 0; i < 2 && !err; i++)
		err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, 0);

	for (i = 0; i < 2 && !err; i++)
		err = m5602_write_bridge(sd, M5602_XB_SIG_INI, 0);

	for (i = 0; i < 2 && !err; i++)
		err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA, 0);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA, (width >> 8) & 0xff);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA, (width & 0xff));
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_SIG_INI, 0);
	return err;
}