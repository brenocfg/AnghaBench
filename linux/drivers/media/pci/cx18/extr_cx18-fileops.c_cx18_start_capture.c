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
struct cx18_stream {scalar_t__ type; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  handle; } ;
struct cx18_open_id {size_t type; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  i_flags; struct cx18_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_CPU_CAPTURE_PAUSE ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  CX18_DEBUG_WARN (char*,...) ; 
 size_t CX18_ENC_STREAM_TYPE_IDX ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_MPG ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_RAD ; 
 size_t CX18_ENC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  CX18_F_I_ENC_PAUSED ; 
 int /*<<< orphan*/  CX18_F_S_APPL_IO ; 
 int /*<<< orphan*/  CX18_F_S_INTERNAL_USE ; 
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int /*<<< orphan*/  CX18_F_S_STREAMOFF ; 
 int EBUSY ; 
 int EIO ; 
 int EPERM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cx18_claim_stream (struct cx18_open_id*,scalar_t__) ; 
 int /*<<< orphan*/  cx18_release_stream (struct cx18_stream*) ; 
 scalar_t__ cx18_start_v4l2_encode_stream (struct cx18_stream*) ; 
 int /*<<< orphan*/  cx18_stop_v4l2_encode_stream (struct cx18_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_vapi (struct cx18*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cx18_start_capture(struct cx18_open_id *id)
{
	struct cx18 *cx = id->cx;
	struct cx18_stream *s = &cx->streams[id->type];
	struct cx18_stream *s_vbi;
	struct cx18_stream *s_idx;

	if (s->type == CX18_ENC_STREAM_TYPE_RAD) {
		/* you cannot read from these stream types. */
		return -EPERM;
	}

	/* Try to claim this stream. */
	if (cx18_claim_stream(id, s->type))
		return -EBUSY;

	/* If capture is already in progress, then we also have to
	   do nothing extra. */
	if (test_bit(CX18_F_S_STREAMOFF, &s->s_flags) ||
	    test_and_set_bit(CX18_F_S_STREAMING, &s->s_flags)) {
		set_bit(CX18_F_S_APPL_IO, &s->s_flags);
		return 0;
	}

	/* Start associated VBI or IDX stream capture if required */
	s_vbi = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
	s_idx = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
	if (s->type == CX18_ENC_STREAM_TYPE_MPG) {
		/*
		 * The VBI and IDX streams should have been claimed
		 * automatically, if for internal use, when the MPG stream was
		 * claimed.  We only need to start these streams capturing.
		 */
		if (test_bit(CX18_F_S_INTERNAL_USE, &s_idx->s_flags) &&
		    !test_and_set_bit(CX18_F_S_STREAMING, &s_idx->s_flags)) {
			if (cx18_start_v4l2_encode_stream(s_idx)) {
				CX18_DEBUG_WARN("IDX capture start failed\n");
				clear_bit(CX18_F_S_STREAMING, &s_idx->s_flags);
				goto start_failed;
			}
			CX18_DEBUG_INFO("IDX capture started\n");
		}
		if (test_bit(CX18_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
		    !test_and_set_bit(CX18_F_S_STREAMING, &s_vbi->s_flags)) {
			if (cx18_start_v4l2_encode_stream(s_vbi)) {
				CX18_DEBUG_WARN("VBI capture start failed\n");
				clear_bit(CX18_F_S_STREAMING, &s_vbi->s_flags);
				goto start_failed;
			}
			CX18_DEBUG_INFO("VBI insertion started\n");
		}
	}

	/* Tell the card to start capturing */
	if (!cx18_start_v4l2_encode_stream(s)) {
		/* We're done */
		set_bit(CX18_F_S_APPL_IO, &s->s_flags);
		/* Resume a possibly paused encoder */
		if (test_and_clear_bit(CX18_F_I_ENC_PAUSED, &cx->i_flags))
			cx18_vapi(cx, CX18_CPU_CAPTURE_PAUSE, 1, s->handle);
		return 0;
	}

start_failed:
	CX18_DEBUG_WARN("Failed to start capturing for stream %s\n", s->name);

	/*
	 * The associated VBI and IDX streams for internal use are released
	 * automatically when the MPG stream is released.  We only need to stop
	 * the associated stream.
	 */
	if (s->type == CX18_ENC_STREAM_TYPE_MPG) {
		/* Stop the IDX stream which is always for internal use */
		if (test_bit(CX18_F_S_STREAMING, &s_idx->s_flags)) {
			cx18_stop_v4l2_encode_stream(s_idx, 0);
			clear_bit(CX18_F_S_STREAMING, &s_idx->s_flags);
		}
		/* Stop the VBI stream, if only running for internal use */
		if (test_bit(CX18_F_S_STREAMING, &s_vbi->s_flags) &&
		    !test_bit(CX18_F_S_APPL_IO, &s_vbi->s_flags)) {
			cx18_stop_v4l2_encode_stream(s_vbi, 0);
			clear_bit(CX18_F_S_STREAMING, &s_vbi->s_flags);
		}
	}
	clear_bit(CX18_F_S_STREAMING, &s->s_flags);
	cx18_release_stream(s); /* Also releases associated streams */
	return -EIO;
}