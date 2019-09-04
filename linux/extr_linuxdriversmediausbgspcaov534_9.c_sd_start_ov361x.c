#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gspca_dev {int curr_mode; int usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
#define  ov361x_1024 133 
#define  ov361x_160 132 
#define  ov361x_1600 131 
#define  ov361x_2048 130 
#define  ov361x_320 129 
#define  ov361x_640 128 
 int /*<<< orphan*/  ov361x_bridge_start_1024 ; 
 int /*<<< orphan*/  ov361x_bridge_start_160 ; 
 int /*<<< orphan*/  ov361x_bridge_start_1600 ; 
 int /*<<< orphan*/  ov361x_bridge_start_2048 ; 
 int /*<<< orphan*/  ov361x_bridge_start_320 ; 
 int /*<<< orphan*/  ov361x_bridge_start_640 ; 
 int ov361x_last ; 
 int /*<<< orphan*/  ov361x_start_1024 ; 
 int /*<<< orphan*/  ov361x_start_160 ; 
 int /*<<< orphan*/  ov361x_start_1600 ; 
 int /*<<< orphan*/  ov361x_start_2048 ; 
 int /*<<< orphan*/  ov361x_start_320 ; 
 int /*<<< orphan*/  ov361x_start_640 ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccb_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccb_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int sd_start_ov361x(struct gspca_dev *gspca_dev)
{
	sccb_write(gspca_dev, 0x12, 0x80);
	msleep(20);
	switch (gspca_dev->curr_mode % (ov361x_last)) {
	case ov361x_2048:
		reg_w_array(gspca_dev, ov361x_bridge_start_2048,
			    ARRAY_SIZE(ov361x_bridge_start_2048));
		sccb_w_array(gspca_dev, ov361x_start_2048,
			     ARRAY_SIZE(ov361x_start_2048));
		break;
	case ov361x_1600:
		reg_w_array(gspca_dev, ov361x_bridge_start_1600,
			    ARRAY_SIZE(ov361x_bridge_start_1600));
		sccb_w_array(gspca_dev, ov361x_start_1600,
			     ARRAY_SIZE(ov361x_start_1600));
		break;
	case ov361x_1024:
		reg_w_array(gspca_dev, ov361x_bridge_start_1024,
			    ARRAY_SIZE(ov361x_bridge_start_1024));
		sccb_w_array(gspca_dev, ov361x_start_1024,
			     ARRAY_SIZE(ov361x_start_1024));
		break;
	case ov361x_640:
		reg_w_array(gspca_dev, ov361x_bridge_start_640,
			    ARRAY_SIZE(ov361x_bridge_start_640));
		sccb_w_array(gspca_dev, ov361x_start_640,
			     ARRAY_SIZE(ov361x_start_640));
		break;
	case ov361x_320:
		reg_w_array(gspca_dev, ov361x_bridge_start_320,
			    ARRAY_SIZE(ov361x_bridge_start_320));
		sccb_w_array(gspca_dev, ov361x_start_320,
			     ARRAY_SIZE(ov361x_start_320));
		break;
	case ov361x_160:
		reg_w_array(gspca_dev, ov361x_bridge_start_160,
			    ARRAY_SIZE(ov361x_bridge_start_160));
		sccb_w_array(gspca_dev, ov361x_start_160,
			     ARRAY_SIZE(ov361x_start_160));
		break;
	}
	reg_w(gspca_dev, 0xe0, 0x00); /* start transfer */

	return gspca_dev->usb_err;
}