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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct si470x_device {int /*<<< orphan*/  usbdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_CARD ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_vidioc_querycap(struct file *file, void *priv,
				  struct v4l2_capability *capability)
{
	struct si470x_device *radio = video_drvdata(file);

	strscpy(capability->driver, DRIVER_NAME, sizeof(capability->driver));
	strscpy(capability->card, DRIVER_CARD, sizeof(capability->card));
	usb_make_path(radio->usbdev, capability->bus_info,
			sizeof(capability->bus_info));
	return 0;
}