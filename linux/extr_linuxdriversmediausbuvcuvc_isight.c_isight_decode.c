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
typedef  int u8 ;
struct uvc_video_queue {int dummy; } ;
struct uvc_buffer {scalar_t__ state; scalar_t__ bytesused; unsigned int length; int* mem; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ UVC_BUF_STATE_ACTIVE ; 
 void* UVC_BUF_STATE_DONE ; 
 int /*<<< orphan*/  UVC_TRACE_FRAME ; 
 scalar_t__ memcmp (int const*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int isight_decode(struct uvc_video_queue *queue, struct uvc_buffer *buf,
		const u8 *data, unsigned int len)
{
	static const u8 hdr[] = {
		0x11, 0x22, 0x33, 0x44,
		0xde, 0xad, 0xbe, 0xef,
		0xde, 0xad, 0xfa, 0xce
	};

	unsigned int maxlen, nbytes;
	u8 *mem;
	int is_header = 0;

	if (buf == NULL)
		return 0;

	if ((len >= 14 && memcmp(&data[2], hdr, 12) == 0) ||
	    (len >= 15 && memcmp(&data[3], hdr, 12) == 0)) {
		uvc_trace(UVC_TRACE_FRAME, "iSight header found\n");
		is_header = 1;
	}

	/* Synchronize to the input stream by waiting for a header packet. */
	if (buf->state != UVC_BUF_STATE_ACTIVE) {
		if (!is_header) {
			uvc_trace(UVC_TRACE_FRAME, "Dropping packet (out of "
				  "sync).\n");
			return 0;
		}

		buf->state = UVC_BUF_STATE_ACTIVE;
	}

	/* Mark the buffer as done if we're at the beginning of a new frame.
	 *
	 * Empty buffers (bytesused == 0) don't trigger end of frame detection
	 * as it doesn't make sense to return an empty buffer.
	 */
	if (is_header && buf->bytesused != 0) {
		buf->state = UVC_BUF_STATE_DONE;
		return -EAGAIN;
	}

	/* Copy the video data to the buffer. Skip header packets, as they
	 * contain no data.
	 */
	if (!is_header) {
		maxlen = buf->length - buf->bytesused;
		mem = buf->mem + buf->bytesused;
		nbytes = min(len, maxlen);
		memcpy(mem, data, nbytes);
		buf->bytesused += nbytes;

		if (len > maxlen || buf->bytesused == buf->length) {
			uvc_trace(UVC_TRACE_FRAME, "Frame complete "
				  "(overflow).\n");
			buf->state = UVC_BUF_STATE_DONE;
		}
	}

	return 0;
}