#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fh {TYPE_2__* vdev; } ;
struct v4l2_capability {int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct uvc_video_chain {int caps; } ;
struct uvc_streaming {TYPE_1__* dev; struct uvc_video_chain* chain; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct uvc_streaming* video_get_drvdata (TYPE_2__*) ; 

__attribute__((used)) static int uvc_meta_v4l2_querycap(struct file *file, void *fh,
				  struct v4l2_capability *cap)
{
	struct v4l2_fh *vfh = file->private_data;
	struct uvc_streaming *stream = video_get_drvdata(vfh->vdev);
	struct uvc_video_chain *chain = stream->chain;

	strscpy(cap->driver, "uvcvideo", sizeof(cap->driver));
	strscpy(cap->card, vfh->vdev->name, sizeof(cap->card));
	usb_make_path(stream->dev->udev, cap->bus_info, sizeof(cap->bus_info));
	cap->capabilities = V4L2_CAP_DEVICE_CAPS | V4L2_CAP_STREAMING
			  | chain->caps;

	return 0;
}