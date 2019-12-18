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
struct gspca_dev {int /*<<< orphan*/ * usb_buf; } ;

/* Variables and functions */
 scalar_t__ D_STREAM ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gspca_debug ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void spca50x_GetFirmware(struct gspca_dev *gspca_dev)
{
	u8 *data;

	if (gspca_debug < D_STREAM)
		return;

	data = gspca_dev->usb_buf;
	reg_r(gspca_dev, 0x20, 0, 5);
	gspca_dbg(gspca_dev, D_STREAM, "FirmWare: %d %d %d %d %d\n",
		  data[0], data[1], data[2], data[3], data[4]);
	reg_r(gspca_dev, 0x23, 0, 64);
	reg_r(gspca_dev, 0x23, 1, 64);
}