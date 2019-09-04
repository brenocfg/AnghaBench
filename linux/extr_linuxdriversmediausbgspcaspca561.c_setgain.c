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
struct gspca_dev {int* usb_buf; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setgain(struct gspca_dev *gspca_dev, s32 val)
{
	/* gain reg low 6 bits  0-63 gain, bit 6 and 7, both double the
	   sensitivity when set, so 31 + one of them set == 63, and 15
	   with both of them set == 63 */
	if (val < 64)
		gspca_dev->usb_buf[0] = val;
	else if (val < 128)
		gspca_dev->usb_buf[0] = (val / 2) | 0x40;
	else
		gspca_dev->usb_buf[0] = (val / 4) | 0xc0;

	gspca_dev->usb_buf[1] = 0;
	reg_w_buf(gspca_dev, 0x8335, 2);
}