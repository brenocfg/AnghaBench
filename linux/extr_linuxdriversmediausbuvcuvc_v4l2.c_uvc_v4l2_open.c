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
struct uvc_streaming {int /*<<< orphan*/  chain; int /*<<< orphan*/  vdev; TYPE_1__* dev; } ;
struct uvc_fh {int /*<<< orphan*/  state; struct uvc_streaming* stream; int /*<<< orphan*/  chain; int /*<<< orphan*/  vfh; } ;
struct file {struct uvc_fh* private_data; } ;
struct TYPE_2__ {scalar_t__ users; int /*<<< orphan*/  lock; int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UVC_HANDLE_PASSIVE ; 
 int /*<<< orphan*/  UVC_TRACE_CALLS ; 
 int /*<<< orphan*/  kfree (struct uvc_fh*) ; 
 struct uvc_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int uvc_status_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct uvc_streaming* video_drvdata (struct file*) ; 

__attribute__((used)) static int uvc_v4l2_open(struct file *file)
{
	struct uvc_streaming *stream;
	struct uvc_fh *handle;
	int ret = 0;

	uvc_trace(UVC_TRACE_CALLS, "uvc_v4l2_open\n");
	stream = video_drvdata(file);

	ret = usb_autopm_get_interface(stream->dev->intf);
	if (ret < 0)
		return ret;

	/* Create the device handle. */
	handle = kzalloc(sizeof(*handle), GFP_KERNEL);
	if (handle == NULL) {
		usb_autopm_put_interface(stream->dev->intf);
		return -ENOMEM;
	}

	mutex_lock(&stream->dev->lock);
	if (stream->dev->users == 0) {
		ret = uvc_status_start(stream->dev, GFP_KERNEL);
		if (ret < 0) {
			mutex_unlock(&stream->dev->lock);
			usb_autopm_put_interface(stream->dev->intf);
			kfree(handle);
			return ret;
		}
	}

	stream->dev->users++;
	mutex_unlock(&stream->dev->lock);

	v4l2_fh_init(&handle->vfh, &stream->vdev);
	v4l2_fh_add(&handle->vfh);
	handle->chain = stream->chain;
	handle->stream = stream;
	handle->state = UVC_HANDLE_PASSIVE;
	file->private_data = handle;

	return 0;
}