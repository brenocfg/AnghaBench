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
struct sd {int /*<<< orphan*/  work_struct; int /*<<< orphan*/  work_thread; int /*<<< orphan*/  gspca_dev; } ;
struct gspca_dev {int curr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 int /*<<< orphan*/  SQ905_CAPTURE_HIGH ; 
 int /*<<< orphan*/  SQ905_CAPTURE_LOW ; 
 int /*<<< orphan*/  SQ905_CAPTURE_MED ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sq905_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *dev = (struct sd *) gspca_dev;
	int ret;

	/* "Open the shutter" and set size, to start capture */
	switch (gspca_dev->curr_mode) {
	default:
/*	case 2: */
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at high resolution\n");
		ret = sq905_command(&dev->gspca_dev, SQ905_CAPTURE_HIGH);
		break;
	case 1:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at medium resolution\n");
		ret = sq905_command(&dev->gspca_dev, SQ905_CAPTURE_MED);
		break;
	case 0:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at low resolution\n");
		ret = sq905_command(&dev->gspca_dev, SQ905_CAPTURE_LOW);
	}

	if (ret < 0) {
		gspca_err(gspca_dev, "Start streaming command failed\n");
		return ret;
	}
	/* Start the workqueue function to do the streaming */
	dev->work_thread = create_singlethread_workqueue(MODULE_NAME);
	queue_work(dev->work_thread, &dev->work_struct);

	return 0;
}