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
struct sur40_state {int /*<<< orphan*/  usbdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_LONG ; 
 int /*<<< orphan*/  DRIVER_SHORT ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sur40_state* video_drvdata (struct file*) ; 

__attribute__((used)) static int sur40_vidioc_querycap(struct file *file, void *priv,
				 struct v4l2_capability *cap)
{
	struct sur40_state *sur40 = video_drvdata(file);

	strlcpy(cap->driver, DRIVER_SHORT, sizeof(cap->driver));
	strlcpy(cap->card, DRIVER_LONG, sizeof(cap->card));
	usb_make_path(sur40->usbdev, cap->bus_info, sizeof(cap->bus_info));
	return 0;
}