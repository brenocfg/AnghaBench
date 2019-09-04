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
struct v4l2_requestbuffers {int dummy; } ;
struct uvc_streaming {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; } ;
struct uvc_fh {struct uvc_streaming* stream; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int uvc_acquire_privileges (struct uvc_fh*) ; 
 int /*<<< orphan*/  uvc_dismiss_privileges (struct uvc_fh*) ; 
 int uvc_request_buffers (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int uvc_ioctl_reqbufs(struct file *file, void *fh,
			     struct v4l2_requestbuffers *rb)
{
	struct uvc_fh *handle = fh;
	struct uvc_streaming *stream = handle->stream;
	int ret;

	ret = uvc_acquire_privileges(handle);
	if (ret < 0)
		return ret;

	mutex_lock(&stream->mutex);
	ret = uvc_request_buffers(&stream->queue, rb);
	mutex_unlock(&stream->mutex);
	if (ret < 0)
		return ret;

	if (ret == 0)
		uvc_dismiss_privileges(handle);

	return 0;
}