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
struct v4l2_format {int dummy; } ;
struct uvc_streaming {int dummy; } ;
struct uvc_fh {struct uvc_streaming* stream; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int uvc_v4l2_get_format (struct uvc_streaming*,struct v4l2_format*) ; 

__attribute__((used)) static int uvc_ioctl_g_fmt_vid_out(struct file *file, void *fh,
				   struct v4l2_format *fmt)
{
	struct uvc_fh *handle = fh;
	struct uvc_streaming *stream = handle->stream;

	return uvc_v4l2_get_format(stream, fmt);
}