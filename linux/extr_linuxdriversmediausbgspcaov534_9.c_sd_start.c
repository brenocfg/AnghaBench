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
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int usb_err; int curr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  QVGA_MODE 131 
 scalar_t__ SENSOR_OV361x ; 
 scalar_t__ SENSOR_OV562x ; 
 scalar_t__ SENSOR_OV971x ; 
#define  SVGA_MODE 130 
#define  VGA_MODE 129 
#define  XGA_MODE 128 
 int /*<<< orphan*/  bridge_start_qvga ; 
 int /*<<< orphan*/  bridge_start_svga ; 
 int /*<<< orphan*/  bridge_start_sxga ; 
 int /*<<< orphan*/  bridge_start_vga ; 
 int /*<<< orphan*/  bridge_start_xga ; 
 int /*<<< orphan*/  ov965x_start_1_svga ; 
 int /*<<< orphan*/  ov965x_start_1_sxga ; 
 int /*<<< orphan*/  ov965x_start_1_vga ; 
 int /*<<< orphan*/  ov965x_start_1_xga ; 
 int /*<<< orphan*/  ov965x_start_2_qvga ; 
 int /*<<< orphan*/  ov965x_start_2_svga ; 
 int /*<<< orphan*/  ov965x_start_2_sxga ; 
 int /*<<< orphan*/  ov965x_start_2_vga ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccb_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_start_ov361x (struct gspca_dev*) ; 
 int /*<<< orphan*/  set_led (struct gspca_dev*,int) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_OV971x)
		return gspca_dev->usb_err;
	if (sd->sensor == SENSOR_OV562x)
		return gspca_dev->usb_err;
	if (sd->sensor == SENSOR_OV361x)
		return sd_start_ov361x(gspca_dev);

	switch (gspca_dev->curr_mode) {
	case QVGA_MODE:			/* 320x240 */
		sccb_w_array(gspca_dev, ov965x_start_1_vga,
				ARRAY_SIZE(ov965x_start_1_vga));
		reg_w_array(gspca_dev, bridge_start_qvga,
				ARRAY_SIZE(bridge_start_qvga));
		sccb_w_array(gspca_dev, ov965x_start_2_qvga,
				ARRAY_SIZE(ov965x_start_2_qvga));
		break;
	case VGA_MODE:			/* 640x480 */
		sccb_w_array(gspca_dev, ov965x_start_1_vga,
				ARRAY_SIZE(ov965x_start_1_vga));
		reg_w_array(gspca_dev, bridge_start_vga,
				ARRAY_SIZE(bridge_start_vga));
		sccb_w_array(gspca_dev, ov965x_start_2_vga,
				ARRAY_SIZE(ov965x_start_2_vga));
		break;
	case SVGA_MODE:			/* 800x600 */
		sccb_w_array(gspca_dev, ov965x_start_1_svga,
				ARRAY_SIZE(ov965x_start_1_svga));
		reg_w_array(gspca_dev, bridge_start_svga,
				ARRAY_SIZE(bridge_start_svga));
		sccb_w_array(gspca_dev, ov965x_start_2_svga,
				ARRAY_SIZE(ov965x_start_2_svga));
		break;
	case XGA_MODE:			/* 1024x768 */
		sccb_w_array(gspca_dev, ov965x_start_1_xga,
				ARRAY_SIZE(ov965x_start_1_xga));
		reg_w_array(gspca_dev, bridge_start_xga,
				ARRAY_SIZE(bridge_start_xga));
		sccb_w_array(gspca_dev, ov965x_start_2_svga,
				ARRAY_SIZE(ov965x_start_2_svga));
		break;
	default:
/*	case SXGA_MODE:			 * 1280x1024 */
		sccb_w_array(gspca_dev, ov965x_start_1_sxga,
				ARRAY_SIZE(ov965x_start_1_sxga));
		reg_w_array(gspca_dev, bridge_start_sxga,
				ARRAY_SIZE(bridge_start_sxga));
		sccb_w_array(gspca_dev, ov965x_start_2_sxga,
				ARRAY_SIZE(ov965x_start_2_sxga));
		break;
	}

	reg_w(gspca_dev, 0xe0, 0x00);
	reg_w(gspca_dev, 0xe0, 0x00);
	set_led(gspca_dev, 1);
	return gspca_dev->usb_err;
}