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
struct sd {int /*<<< orphan*/  work_struct; } ;
struct gspca_dev {scalar_t__ present; int /*<<< orphan*/  usb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vicam_set_camera_power (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_stop0(struct gspca_dev *gspca_dev)
{
	struct sd *dev = (struct sd *)gspca_dev;

	/* wait for the work queue to terminate */
	mutex_unlock(&gspca_dev->usb_lock);
	/* This waits for vicam_dostream to finish */
	flush_work(&dev->work_struct);
	mutex_lock(&gspca_dev->usb_lock);

	if (gspca_dev->present)
		vicam_set_camera_power(gspca_dev, 0);
}