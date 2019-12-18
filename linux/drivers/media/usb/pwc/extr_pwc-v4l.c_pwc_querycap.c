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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct pwc_device {int /*<<< orphan*/  udev; TYPE_1__ vdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWC_NAME ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pwc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int pwc_querycap(struct file *file, void *fh, struct v4l2_capability *cap)
{
	struct pwc_device *pdev = video_drvdata(file);

	strscpy(cap->driver, PWC_NAME, sizeof(cap->driver));
	strscpy(cap->card, pdev->vdev.name, sizeof(cap->card));
	usb_make_path(pdev->udev, cap->bus_info, sizeof(cap->bus_info));
	return 0;
}