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
typedef  void* u8 ;
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 

__attribute__((used)) static void mi_w(struct gspca_dev *gspca_dev,
		 u8 addr,
		 u8 value)
{
	gspca_dev->usb_buf[0] = 0x1f;
	gspca_dev->usb_buf[1] = 0;			/* control byte */
	gspca_dev->usb_buf[2] = addr;
	gspca_dev->usb_buf[3] = value;

	reg_w(gspca_dev, 4);
}