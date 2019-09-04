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
struct v4l2_exportbuffer {int dummy; } ;
struct uvc_streaming {int /*<<< orphan*/  queue; } ;
struct uvc_fh {struct uvc_streaming* stream; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int uvc_export_buffer (int /*<<< orphan*/ *,struct v4l2_exportbuffer*) ; 
 int /*<<< orphan*/  uvc_has_privileges (struct uvc_fh*) ; 

__attribute__((used)) static int uvc_ioctl_expbuf(struct file *file, void *fh,
			    struct v4l2_exportbuffer *exp)
{
	struct uvc_fh *handle = fh;
	struct uvc_streaming *stream = handle->stream;

	if (!uvc_has_privileges(handle))
		return -EBUSY;

	return uvc_export_buffer(&stream->queue, exp);
}