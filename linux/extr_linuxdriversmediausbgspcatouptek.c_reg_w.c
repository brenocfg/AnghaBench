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
typedef  int u16 ;
struct gspca_dev {char* usb_buf; int usb_err; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBO ; 
 int EIO ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,int,int,...) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,char*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ val_reply (struct gspca_dev*,char*,int) ; 

__attribute__((used)) static void reg_w(struct gspca_dev *gspca_dev, u16 value, u16 index)
{
	char *buff = gspca_dev->usb_buf;
	int rc;

	gspca_dbg(gspca_dev, D_USBO,
		  "reg_w bReq=0x0B, bReqT=0xC0, wVal=0x%04X, wInd=0x%04X\n\n",
		  value, index);
	rc = usb_control_msg(gspca_dev->dev, usb_rcvctrlpipe(gspca_dev->dev, 0),
		0x0B, 0xC0, value, index, buff, 1, 500);
	gspca_dbg(gspca_dev, D_USBO, "rc=%d, ret={0x%02x}\n", rc, (int)buff[0]);
	if (rc < 0) {
		gspca_err(gspca_dev, "Failed reg_w(0x0B, 0xC0, 0x%04X, 0x%04X) w/ rc %d\n",
			  value, index, rc);
		gspca_dev->usb_err = rc;
		return;
	}
	if (val_reply(gspca_dev, buff, rc)) {
		gspca_err(gspca_dev, "Bad reply to reg_w(0x0B, 0xC0, 0x%04X, 0x%04X\n",
			  value, index);
		gspca_dev->usb_err = -EIO;
	}
}