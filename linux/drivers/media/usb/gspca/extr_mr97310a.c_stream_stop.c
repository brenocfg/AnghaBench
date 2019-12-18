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

/* Variables and functions */
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 scalar_t__ mr_write (struct gspca_dev*,int) ; 

__attribute__((used)) static void stream_stop(struct gspca_dev *gspca_dev)
{
	gspca_dev->usb_buf[0] = 0x01;
	gspca_dev->usb_buf[1] = 0x00;
	if (mr_write(gspca_dev, 2) < 0)
		gspca_err(gspca_dev, "Stream Stop failed\n");
}