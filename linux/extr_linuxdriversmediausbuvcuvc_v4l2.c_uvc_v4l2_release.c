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
struct uvc_streaming {TYPE_1__* dev; int /*<<< orphan*/  queue; } ;
struct uvc_fh {int /*<<< orphan*/  vfh; struct uvc_streaming* stream; } ;
struct file {struct uvc_fh* private_data; } ;
struct TYPE_2__ {scalar_t__ users; int /*<<< orphan*/  intf; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_TRACE_CALLS ; 
 int /*<<< orphan*/  kfree (struct uvc_fh*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_dismiss_privileges (struct uvc_fh*) ; 
 scalar_t__ uvc_has_privileges (struct uvc_fh*) ; 
 int /*<<< orphan*/  uvc_queue_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_status_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uvc_v4l2_release(struct file *file)
{
	struct uvc_fh *handle = file->private_data;
	struct uvc_streaming *stream = handle->stream;

	uvc_trace(UVC_TRACE_CALLS, "uvc_v4l2_release\n");

	/* Only free resources if this is a privileged handle. */
	if (uvc_has_privileges(handle))
		uvc_queue_release(&stream->queue);

	/* Release the file handle. */
	uvc_dismiss_privileges(handle);
	v4l2_fh_del(&handle->vfh);
	v4l2_fh_exit(&handle->vfh);
	kfree(handle);
	file->private_data = NULL;

	mutex_lock(&stream->dev->lock);
	if (--stream->dev->users == 0)
		uvc_status_stop(stream->dev);
	mutex_unlock(&stream->dev->lock);

	usb_autopm_put_interface(stream->dev->intf);
	return 0;
}