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
struct TYPE_2__ {int /*<<< orphan*/ * v4l2_dev; } ;
struct ivtv_stream {int /*<<< orphan*/  s_flags; TYPE_1__ vdev; } ;
struct ivtv {scalar_t__ output_mode; int /*<<< orphan*/  cxhdl; int /*<<< orphan*/  capturing; int /*<<< orphan*/  decoding; struct ivtv_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_START_PLAYBACK ; 
 int /*<<< orphan*/  CX2341X_DEC_STOP_PLAYBACK ; 
 int /*<<< orphan*/  CX2341X_ENC_START_CAPTURE ; 
 int /*<<< orphan*/  CX2341X_ENC_STOP_CAPTURE ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 size_t IVTV_DEC_STREAM_TYPE_YUV ; 
 size_t IVTV_ENC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  IVTV_F_S_PASSTHROUGH ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMING ; 
 scalar_t__ OUT_NONE ; 
 scalar_t__ OUT_PASSTHROUGH ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx2341x_handler_set_busy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cx2341x_handler_setup (int /*<<< orphan*/ *) ; 
 scalar_t__ ivtv_set_output_mode (struct ivtv*,scalar_t__) ; 
 int /*<<< orphan*/  ivtv_setup_v4l2_decode_stream (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int,int,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ivtv_passthrough_mode(struct ivtv *itv, int enable)
{
	struct ivtv_stream *yuv_stream = &itv->streams[IVTV_ENC_STREAM_TYPE_YUV];
	struct ivtv_stream *dec_stream = &itv->streams[IVTV_DEC_STREAM_TYPE_YUV];

	if (yuv_stream->vdev.v4l2_dev == NULL || dec_stream->vdev.v4l2_dev == NULL)
		return -EINVAL;

	IVTV_DEBUG_INFO("ivtv ioctl: Select passthrough mode\n");

	/* Prevent others from starting/stopping streams while we
	   initiate/terminate passthrough mode */
	if (enable) {
		if (itv->output_mode == OUT_PASSTHROUGH) {
			return 0;
		}
		if (ivtv_set_output_mode(itv, OUT_PASSTHROUGH) != OUT_PASSTHROUGH)
			return -EBUSY;

		/* Fully initialize stream, and then unflag init */
		set_bit(IVTV_F_S_PASSTHROUGH, &dec_stream->s_flags);
		set_bit(IVTV_F_S_STREAMING, &dec_stream->s_flags);

		/* Setup YUV Decoder */
		ivtv_setup_v4l2_decode_stream(dec_stream);

		/* Start Decoder */
		ivtv_vapi(itv, CX2341X_DEC_START_PLAYBACK, 2, 0, 1);
		atomic_inc(&itv->decoding);

		/* Setup capture if not already done */
		if (atomic_read(&itv->capturing) == 0) {
			cx2341x_handler_setup(&itv->cxhdl);
			cx2341x_handler_set_busy(&itv->cxhdl, 1);
		}

		/* Start Passthrough Mode */
		ivtv_vapi(itv, CX2341X_ENC_START_CAPTURE, 2, 2, 11);
		atomic_inc(&itv->capturing);
		return 0;
	}

	if (itv->output_mode != OUT_PASSTHROUGH)
		return 0;

	/* Stop Passthrough Mode */
	ivtv_vapi(itv, CX2341X_ENC_STOP_CAPTURE, 3, 1, 2, 11);
	ivtv_vapi(itv, CX2341X_DEC_STOP_PLAYBACK, 3, 1, 0, 0);

	atomic_dec(&itv->capturing);
	atomic_dec(&itv->decoding);
	clear_bit(IVTV_F_S_PASSTHROUGH, &dec_stream->s_flags);
	clear_bit(IVTV_F_S_STREAMING, &dec_stream->s_flags);
	itv->output_mode = OUT_NONE;
	if (atomic_read(&itv->capturing) == 0)
		cx2341x_handler_set_busy(&itv->cxhdl, 0);

	return 0;
}