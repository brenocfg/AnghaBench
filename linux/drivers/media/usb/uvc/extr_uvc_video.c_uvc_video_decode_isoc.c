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
typedef  int /*<<< orphan*/  u8 ;
struct uvc_urb {struct uvc_streaming* stream; struct urb* urb; } ;
struct uvc_streaming {int dummy; } ;
struct uvc_buffer {int error; scalar_t__ state; } ;
struct urb {int number_of_packets; TYPE_1__* iso_frame_desc; int /*<<< orphan*/ * transfer_buffer; } ;
struct TYPE_2__ {scalar_t__ status; int offset; scalar_t__ actual_length; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ UVC_BUF_STATE_READY ; 
 int /*<<< orphan*/  UVC_TRACE_FRAME ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  uvc_video_decode_data (struct uvc_urb*,struct uvc_buffer*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  uvc_video_decode_end (struct uvc_streaming*,struct uvc_buffer*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  uvc_video_decode_meta (struct uvc_streaming*,struct uvc_buffer*,int /*<<< orphan*/ *,int) ; 
 int uvc_video_decode_start (struct uvc_streaming*,struct uvc_buffer*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  uvc_video_next_buffers (struct uvc_streaming*,struct uvc_buffer**,struct uvc_buffer**) ; 

__attribute__((used)) static void uvc_video_decode_isoc(struct uvc_urb *uvc_urb,
			struct uvc_buffer *buf, struct uvc_buffer *meta_buf)
{
	struct urb *urb = uvc_urb->urb;
	struct uvc_streaming *stream = uvc_urb->stream;
	u8 *mem;
	int ret, i;

	for (i = 0; i < urb->number_of_packets; ++i) {
		if (urb->iso_frame_desc[i].status < 0) {
			uvc_trace(UVC_TRACE_FRAME, "USB isochronous frame "
				"lost (%d).\n", urb->iso_frame_desc[i].status);
			/* Mark the buffer as faulty. */
			if (buf != NULL)
				buf->error = 1;
			continue;
		}

		/* Decode the payload header. */
		mem = urb->transfer_buffer + urb->iso_frame_desc[i].offset;
		do {
			ret = uvc_video_decode_start(stream, buf, mem,
				urb->iso_frame_desc[i].actual_length);
			if (ret == -EAGAIN)
				uvc_video_next_buffers(stream, &buf, &meta_buf);
		} while (ret == -EAGAIN);

		if (ret < 0)
			continue;

		uvc_video_decode_meta(stream, meta_buf, mem, ret);

		/* Decode the payload data. */
		uvc_video_decode_data(uvc_urb, buf, mem + ret,
			urb->iso_frame_desc[i].actual_length - ret);

		/* Process the header again. */
		uvc_video_decode_end(stream, buf, mem,
			urb->iso_frame_desc[i].actual_length);

		if (buf->state == UVC_BUF_STATE_READY)
			uvc_video_next_buffers(stream, &buf, &meta_buf);
	}
}