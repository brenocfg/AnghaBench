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
typedef  int /*<<< orphan*/  u8 ;
struct uvc_streaming {int dummy; } ;
struct uvc_buffer {unsigned int length; unsigned int bytesused; int error; int /*<<< orphan*/  state; void* mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_BUF_STATE_READY ; 
 int /*<<< orphan*/  UVC_TRACE_FRAME ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void uvc_video_decode_data(struct uvc_streaming *stream,
		struct uvc_buffer *buf, const u8 *data, int len)
{
	unsigned int maxlen, nbytes;
	void *mem;

	if (len <= 0)
		return;

	/* Copy the video data to the buffer. */
	maxlen = buf->length - buf->bytesused;
	mem = buf->mem + buf->bytesused;
	nbytes = min((unsigned int)len, maxlen);
	memcpy(mem, data, nbytes);
	buf->bytesused += nbytes;

	/* Complete the current frame if the buffer size was exceeded. */
	if (len > maxlen) {
		uvc_trace(UVC_TRACE_FRAME, "Frame complete (overflow).\n");
		buf->error = 1;
		buf->state = UVC_BUF_STATE_READY;
	}
}