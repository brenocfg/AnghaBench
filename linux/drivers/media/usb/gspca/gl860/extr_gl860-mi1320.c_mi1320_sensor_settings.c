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
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {scalar_t__ curr_mode; TYPE_2__ cam; } ;
typedef  size_t s32 ;
struct TYPE_3__ {size_t priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  IMAGE_1280 129 
#define  IMAGE_800 128 
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetch_validx (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** tbl_1280 ; 
 int /*<<< orphan*/ ** tbl_640 ; 
 int /*<<< orphan*/ ** tbl_800 ; 
 int /*<<< orphan*/  tbl_sensor_settings_1280 ; 
 int /*<<< orphan*/  tbl_sensor_settings_640 ; 
 int /*<<< orphan*/  tbl_sensor_settings_800 ; 
 int /*<<< orphan*/  tbl_sensor_settings_common ; 

__attribute__((used)) static int mi1320_sensor_settings(struct gspca_dev *gspca_dev)
{
	s32 reso = gspca_dev->cam.cam_mode[(s32) gspca_dev->curr_mode].priv;

	ctrl_out(gspca_dev, 0x40, 5, 0x0001, 0x0000, 0, NULL);

	fetch_validx(gspca_dev, tbl_sensor_settings_common,
				ARRAY_SIZE(tbl_sensor_settings_common));

	switch (reso) {
	case IMAGE_1280:
		fetch_validx(gspca_dev, tbl_sensor_settings_1280,
					ARRAY_SIZE(tbl_sensor_settings_1280));
		ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 64, tbl_1280[0]);
		ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 40, tbl_1280[1]);
		ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200, 12, tbl_1280[2]);
		break;

	case IMAGE_800:
		fetch_validx(gspca_dev, tbl_sensor_settings_800,
					ARRAY_SIZE(tbl_sensor_settings_800));
		ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 64, tbl_800[0]);
		ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 40, tbl_800[1]);
		ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200, 12, tbl_800[2]);
		break;

	default:
		fetch_validx(gspca_dev, tbl_sensor_settings_640,
					ARRAY_SIZE(tbl_sensor_settings_640));
		ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 60, tbl_640[0]);
		ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 40, tbl_640[1]);
		ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200, 12, tbl_640[2]);
		break;
	}
	return 0;
}