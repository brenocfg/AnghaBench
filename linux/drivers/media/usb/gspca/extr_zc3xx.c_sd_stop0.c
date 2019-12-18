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
struct sd {int /*<<< orphan*/  sensor; int /*<<< orphan*/  work; } ;
struct gspca_dev {int /*<<< orphan*/  present; int /*<<< orphan*/  usb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_unknown (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_stop0(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	mutex_unlock(&gspca_dev->usb_lock);
	flush_work(&sd->work);
	mutex_lock(&gspca_dev->usb_lock);
	if (!gspca_dev->present)
		return;
	send_unknown(gspca_dev, sd->sensor);
}