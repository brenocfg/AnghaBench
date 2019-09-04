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
struct uvc_streaming {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; } ;
struct uvc_fh {struct uvc_streaming* stream; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_has_privileges (struct uvc_fh*) ; 
 int uvc_queue_streamon (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int uvc_ioctl_streamon(struct file *file, void *fh,
			      enum v4l2_buf_type type)
{
	struct uvc_fh *handle = fh;
	struct uvc_streaming *stream = handle->stream;
	int ret;

	if (!uvc_has_privileges(handle))
		return -EBUSY;

	mutex_lock(&stream->mutex);
	ret = uvc_queue_streamon(&stream->queue, type);
	mutex_unlock(&stream->mutex);

	return ret;
}