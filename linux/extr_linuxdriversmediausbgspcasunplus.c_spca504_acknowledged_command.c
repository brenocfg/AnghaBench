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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct gspca_dev {int /*<<< orphan*/ * usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_FRAM ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spca504_acknowledged_command(struct gspca_dev *gspca_dev,
			     u8 req, u16 idx, u16 val)
{
	reg_w_riv(gspca_dev, req, idx, val);
	reg_r(gspca_dev, 0x01, 0x0001, 1);
	gspca_dbg(gspca_dev, D_FRAM, "before wait 0x%04x\n",
		  gspca_dev->usb_buf[0]);
	reg_w_riv(gspca_dev, req, idx, val);

	msleep(200);
	reg_r(gspca_dev, 0x01, 0x0001, 1);
	gspca_dbg(gspca_dev, D_FRAM, "after wait 0x%04x\n",
		  gspca_dev->usb_buf[0]);
}