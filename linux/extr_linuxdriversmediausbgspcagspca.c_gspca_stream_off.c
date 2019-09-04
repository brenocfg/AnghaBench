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
struct gspca_dev {int streaming; TYPE_1__* sd_desc; scalar_t__ present; scalar_t__ usb_err; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop0 ) (struct gspca_dev*) ;int /*<<< orphan*/  (* stopN ) (struct gspca_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  destroy_urbs (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_input_create_urb (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_input_destroy_urb (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_set_alt0 (struct gspca_dev*) ; 
 int /*<<< orphan*/  stub1 (struct gspca_dev*) ; 
 int /*<<< orphan*/  stub2 (struct gspca_dev*) ; 

__attribute__((used)) static void gspca_stream_off(struct gspca_dev *gspca_dev)
{
	gspca_dev->streaming = false;
	gspca_dev->usb_err = 0;
	if (gspca_dev->sd_desc->stopN)
		gspca_dev->sd_desc->stopN(gspca_dev);
	destroy_urbs(gspca_dev);
	gspca_input_destroy_urb(gspca_dev);
	gspca_set_alt0(gspca_dev);
	if (gspca_dev->present)
		gspca_input_create_urb(gspca_dev);
	if (gspca_dev->sd_desc->stop0)
		gspca_dev->sd_desc->stop0(gspca_dev);
	gspca_dbg(gspca_dev, D_STREAM, "stream off OK\n");
}