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
struct gspca_dev {scalar_t__ usb_err; int /*<<< orphan*/ * usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBI ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  reg_r_i (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void reg_r(struct gspca_dev *gspca_dev,
		  u16 req,
		  u16 index,
		  u16 len)
{
	reg_r_i(gspca_dev, req, index, len);
	if (gspca_dev->usb_err < 0)
		return;
	if (len == 1)
		gspca_dbg(gspca_dev, D_USBI, "GET %02x 0001 %04x %02x\n",
			  req, index,
			  gspca_dev->usb_buf[0]);
	else
		gspca_dbg(gspca_dev, D_USBI, "GET %02x 0001 %04x %*ph\n",
			  req, index, 3, gspca_dev->usb_buf);
}