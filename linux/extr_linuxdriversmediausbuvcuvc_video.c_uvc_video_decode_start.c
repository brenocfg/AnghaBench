#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  nb_invalid; } ;
struct TYPE_7__ {TYPE_1__ frame; } ;
struct uvc_streaming {int last_fid; scalar_t__ sequence; TYPE_3__* dev; TYPE_2__ stats; } ;
struct TYPE_9__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_10__ {TYPE_4__ vb2_buf; scalar_t__ sequence; int /*<<< orphan*/  field; } ;
struct uvc_buffer {int error; scalar_t__ state; scalar_t__ bytesused; TYPE_5__ buf; } ;
struct TYPE_8__ {int quirks; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENODATA ; 
 scalar_t__ UVC_BUF_STATE_ACTIVE ; 
 scalar_t__ UVC_BUF_STATE_READY ; 
 int UVC_QUIRK_STREAM_NO_FID ; 
 int const UVC_STREAM_EOF ; 
 int const UVC_STREAM_ERR ; 
 int const UVC_STREAM_FID ; 
 int /*<<< orphan*/  UVC_TRACE_FRAME ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uvc_video_clock_decode (struct uvc_streaming*,struct uvc_buffer*,int const*,int) ; 
 int /*<<< orphan*/  uvc_video_get_time () ; 
 int /*<<< orphan*/  uvc_video_stats_decode (struct uvc_streaming*,int const*,int) ; 
 int /*<<< orphan*/  uvc_video_stats_update (struct uvc_streaming*) ; 

__attribute__((used)) static int uvc_video_decode_start(struct uvc_streaming *stream,
		struct uvc_buffer *buf, const u8 *data, int len)
{
	u8 fid;

	/* Sanity checks:
	 * - packet must be at least 2 bytes long
	 * - bHeaderLength value must be at least 2 bytes (see above)
	 * - bHeaderLength value can't be larger than the packet size.
	 */
	if (len < 2 || data[0] < 2 || data[0] > len) {
		stream->stats.frame.nb_invalid++;
		return -EINVAL;
	}

	fid = data[1] & UVC_STREAM_FID;

	/* Increase the sequence number regardless of any buffer states, so
	 * that discontinuous sequence numbers always indicate lost frames.
	 */
	if (stream->last_fid != fid) {
		stream->sequence++;
		if (stream->sequence)
			uvc_video_stats_update(stream);
	}

	uvc_video_clock_decode(stream, buf, data, len);
	uvc_video_stats_decode(stream, data, len);

	/* Store the payload FID bit and return immediately when the buffer is
	 * NULL.
	 */
	if (buf == NULL) {
		stream->last_fid = fid;
		return -ENODATA;
	}

	/* Mark the buffer as bad if the error bit is set. */
	if (data[1] & UVC_STREAM_ERR) {
		uvc_trace(UVC_TRACE_FRAME, "Marking buffer as bad (error bit "
			  "set).\n");
		buf->error = 1;
	}

	/* Synchronize to the input stream by waiting for the FID bit to be
	 * toggled when the the buffer state is not UVC_BUF_STATE_ACTIVE.
	 * stream->last_fid is initialized to -1, so the first isochronous
	 * frame will always be in sync.
	 *
	 * If the device doesn't toggle the FID bit, invert stream->last_fid
	 * when the EOF bit is set to force synchronisation on the next packet.
	 */
	if (buf->state != UVC_BUF_STATE_ACTIVE) {
		if (fid == stream->last_fid) {
			uvc_trace(UVC_TRACE_FRAME, "Dropping payload (out of "
				"sync).\n");
			if ((stream->dev->quirks & UVC_QUIRK_STREAM_NO_FID) &&
			    (data[1] & UVC_STREAM_EOF))
				stream->last_fid ^= UVC_STREAM_FID;
			return -ENODATA;
		}

		buf->buf.field = V4L2_FIELD_NONE;
		buf->buf.sequence = stream->sequence;
		buf->buf.vb2_buf.timestamp = ktime_to_ns(uvc_video_get_time());

		/* TODO: Handle PTS and SCR. */
		buf->state = UVC_BUF_STATE_ACTIVE;
	}

	/* Mark the buffer as done if we're at the beginning of a new frame.
	 * End of frame detection is better implemented by checking the EOF
	 * bit (FID bit toggling is delayed by one frame compared to the EOF
	 * bit), but some devices don't set the bit at end of frame (and the
	 * last payload can be lost anyway). We thus must check if the FID has
	 * been toggled.
	 *
	 * stream->last_fid is initialized to -1, so the first isochronous
	 * frame will never trigger an end of frame detection.
	 *
	 * Empty buffers (bytesused == 0) don't trigger end of frame detection
	 * as it doesn't make sense to return an empty buffer. This also
	 * avoids detecting end of frame conditions at FID toggling if the
	 * previous payload had the EOF bit set.
	 */
	if (fid != stream->last_fid && buf->bytesused != 0) {
		uvc_trace(UVC_TRACE_FRAME, "Frame complete (FID bit "
				"toggled).\n");
		buf->state = UVC_BUF_STATE_READY;
		return -EAGAIN;
	}

	stream->last_fid = fid;

	return data[0];
}