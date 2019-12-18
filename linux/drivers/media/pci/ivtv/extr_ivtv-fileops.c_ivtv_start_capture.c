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
struct ivtv_stream {scalar_t__ type; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  name; } ;
struct ivtv_open_id {size_t type; struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  i_flags; struct ivtv_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_PAUSE_ENCODER ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*,...) ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_MPG ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_VBI ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_VOUT ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_YUV ; 
 scalar_t__ IVTV_ENC_STREAM_TYPE_MPG ; 
 scalar_t__ IVTV_ENC_STREAM_TYPE_RAD ; 
 size_t IVTV_ENC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  IVTV_F_I_ENC_PAUSED ; 
 int /*<<< orphan*/  IVTV_F_S_APPL_IO ; 
 int /*<<< orphan*/  IVTV_F_S_INTERNAL_USE ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMING ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMOFF ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ivtv_claim_stream (struct ivtv_open_id*,scalar_t__) ; 
 int /*<<< orphan*/  ivtv_release_stream (struct ivtv_stream*) ; 
 scalar_t__ ivtv_start_v4l2_encode_stream (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_stop_v4l2_encode_stream (struct ivtv_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ivtv_start_capture(struct ivtv_open_id *id)
{
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[id->type];
	struct ivtv_stream *s_vbi;

	if (s->type == IVTV_ENC_STREAM_TYPE_RAD ||
	    s->type == IVTV_DEC_STREAM_TYPE_MPG ||
	    s->type == IVTV_DEC_STREAM_TYPE_YUV ||
	    s->type == IVTV_DEC_STREAM_TYPE_VOUT) {
		/* you cannot read from these stream types. */
		return -EINVAL;
	}

	/* Try to claim this stream. */
	if (ivtv_claim_stream(id, s->type))
		return -EBUSY;

	/* This stream does not need to start capturing */
	if (s->type == IVTV_DEC_STREAM_TYPE_VBI) {
		set_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		return 0;
	}

	/* If capture is already in progress, then we also have to
	   do nothing extra. */
	if (test_bit(IVTV_F_S_STREAMOFF, &s->s_flags) || test_and_set_bit(IVTV_F_S_STREAMING, &s->s_flags)) {
		set_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		return 0;
	}

	/* Start VBI capture if required */
	s_vbi = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
	if (s->type == IVTV_ENC_STREAM_TYPE_MPG &&
	    test_bit(IVTV_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
	    !test_and_set_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags)) {
		/* Note: the IVTV_ENC_STREAM_TYPE_VBI is claimed
		   automatically when the MPG stream is claimed.
		   We only need to start the VBI capturing. */
		if (ivtv_start_v4l2_encode_stream(s_vbi)) {
			IVTV_DEBUG_WARN("VBI capture start failed\n");

			/* Failure, clean up and return an error */
			clear_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags);
			clear_bit(IVTV_F_S_STREAMING, &s->s_flags);
			/* also releases the associated VBI stream */
			ivtv_release_stream(s);
			return -EIO;
		}
		IVTV_DEBUG_INFO("VBI insertion started\n");
	}

	/* Tell the card to start capturing */
	if (!ivtv_start_v4l2_encode_stream(s)) {
		/* We're done */
		set_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		/* Resume a possibly paused encoder */
		if (test_and_clear_bit(IVTV_F_I_ENC_PAUSED, &itv->i_flags))
			ivtv_vapi(itv, CX2341X_ENC_PAUSE_ENCODER, 1, 1);
		return 0;
	}

	/* failure, clean up */
	IVTV_DEBUG_WARN("Failed to start capturing for stream %s\n", s->name);

	/* Note: the IVTV_ENC_STREAM_TYPE_VBI is released
	   automatically when the MPG stream is released.
	   We only need to stop the VBI capturing. */
	if (s->type == IVTV_ENC_STREAM_TYPE_MPG &&
	    test_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags)) {
		ivtv_stop_v4l2_encode_stream(s_vbi, 0);
		clear_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags);
	}
	clear_bit(IVTV_F_S_STREAMING, &s->s_flags);
	ivtv_release_stream(s);
	return -EIO;
}