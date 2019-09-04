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
struct TYPE_3__ {scalar_t__ dwMaxVideoFrameSize; } ;
struct uvc_streaming {TYPE_2__* cur_format; TYPE_1__ ctrl; } ;
struct uvc_buffer {scalar_t__ bytesused; int error; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int UVC_FMT_FLAG_COMPRESSED ; 

__attribute__((used)) static void uvc_video_validate_buffer(const struct uvc_streaming *stream,
				      struct uvc_buffer *buf)
{
	if (stream->ctrl.dwMaxVideoFrameSize != buf->bytesused &&
	    !(stream->cur_format->flags & UVC_FMT_FLAG_COMPRESSED))
		buf->error = 1;
}