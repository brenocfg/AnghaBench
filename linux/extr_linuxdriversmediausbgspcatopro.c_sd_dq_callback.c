#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {int ag_cnt; int /*<<< orphan*/  bridge; } ;
struct TYPE_2__ {int width; } ;
struct gspca_dev {int* usb_buf; int /*<<< orphan*/  exposure; TYPE_1__ pixfmt; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AG_CNT_START ; 
 int /*<<< orphan*/  BRIDGE_TP6810 ; 
 int gspca_expo_autogain (struct gspca_dev*,int,int,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  setframerate (struct gspca_dev*,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_dq_callback(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret, alen;
	int luma, expo;

	if (sd->ag_cnt < 0)
		return;
	if (--sd->ag_cnt > 5)
		return;
	switch (sd->ag_cnt) {
/*	case 5: */
	default:
		reg_w(gspca_dev, 0x7d, 0x00);
		break;
	case 4:
		reg_w(gspca_dev, 0x27, 0xb0);
		break;
	case 3:
		reg_w(gspca_dev, 0x0c, 0x01);
		break;
	case 2:
		ret = usb_bulk_msg(gspca_dev->dev,
				usb_rcvbulkpipe(gspca_dev->dev, 0x02),
				gspca_dev->usb_buf,
				32,
				&alen,
				500);
		if (ret < 0) {
			pr_err("bulk err %d\n", ret);
			break;
		}
		/* values not used (unknown) */
		break;
	case 1:
		reg_w(gspca_dev, 0x27, 0xd0);
		break;
	case 0:
		ret = usb_bulk_msg(gspca_dev->dev,
				usb_rcvbulkpipe(gspca_dev->dev, 0x02),
				gspca_dev->usb_buf,
				32,
				&alen,
				500);
		if (ret < 0) {
			pr_err("bulk err %d\n", ret);
			break;
		}
		luma = ((gspca_dev->usb_buf[8] << 8) + gspca_dev->usb_buf[7] +
			(gspca_dev->usb_buf[11] << 8) + gspca_dev->usb_buf[10] +
			(gspca_dev->usb_buf[14] << 8) + gspca_dev->usb_buf[13] +
			(gspca_dev->usb_buf[17] << 8) + gspca_dev->usb_buf[16] +
			(gspca_dev->usb_buf[20] << 8) + gspca_dev->usb_buf[19] +
			(gspca_dev->usb_buf[23] << 8) + gspca_dev->usb_buf[22] +
			(gspca_dev->usb_buf[26] << 8) + gspca_dev->usb_buf[25] +
			(gspca_dev->usb_buf[29] << 8) + gspca_dev->usb_buf[28])
				/ 8;
		if (gspca_dev->pixfmt.width == 640)
			luma /= 4;
		reg_w(gspca_dev, 0x7d, 0x00);

		expo = v4l2_ctrl_g_ctrl(gspca_dev->exposure);
		ret = gspca_expo_autogain(gspca_dev, luma,
				60,	/* desired luma */
				6,	/* dead zone */
				2,	/* gain knee */
				70);	/* expo knee */
		sd->ag_cnt = AG_CNT_START;
		if (sd->bridge == BRIDGE_TP6810) {
			int new_expo = v4l2_ctrl_g_ctrl(gspca_dev->exposure);

			if ((expo >= 128 && new_expo < 128)
			 || (expo < 128 && new_expo >= 128))
				setframerate(gspca_dev, new_expo);
		}
		break;
	}
}