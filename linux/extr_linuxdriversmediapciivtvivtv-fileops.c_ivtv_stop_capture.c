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
struct ivtv_stream {int /*<<< orphan*/  s_flags; int /*<<< orphan*/ * fh; int /*<<< orphan*/  name; } ;
struct ivtv_open_id {size_t type; struct ivtv* itv; } ;
struct ivtv {struct ivtv_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_FILE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 size_t IVTV_DEC_STREAM_TYPE_VBI ; 
 size_t IVTV_ENC_STREAM_TYPE_MPG ; 
 size_t IVTV_ENC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  IVTV_F_S_APPL_IO ; 
 int /*<<< orphan*/  IVTV_F_S_INTERNAL_USE ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMING ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMOFF ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_release_stream (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_stop_v4l2_encode_stream (struct ivtv_stream*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ivtv_stop_capture(struct ivtv_open_id *id, int gop_end)
{
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[id->type];

	IVTV_DEBUG_FILE("close() of %s\n", s->name);

	/* 'Unclaim' this stream */

	/* Stop capturing */
	if (test_bit(IVTV_F_S_STREAMING, &s->s_flags)) {
		struct ivtv_stream *s_vbi = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];

		IVTV_DEBUG_INFO("close stopping capture\n");
		/* Special case: a running VBI capture for VBI insertion
		   in the mpeg stream. Need to stop that too. */
		if (id->type == IVTV_ENC_STREAM_TYPE_MPG &&
		    test_bit(IVTV_F_S_STREAMING, &s_vbi->s_flags) &&
		    !test_bit(IVTV_F_S_APPL_IO, &s_vbi->s_flags)) {
			IVTV_DEBUG_INFO("close stopping embedded VBI capture\n");
			ivtv_stop_v4l2_encode_stream(s_vbi, 0);
		}
		if ((id->type == IVTV_DEC_STREAM_TYPE_VBI ||
		     id->type == IVTV_ENC_STREAM_TYPE_VBI) &&
		    test_bit(IVTV_F_S_INTERNAL_USE, &s->s_flags)) {
			/* Also used internally, don't stop capturing */
			s->fh = NULL;
		}
		else {
			ivtv_stop_v4l2_encode_stream(s, gop_end);
		}
	}
	if (!gop_end) {
		clear_bit(IVTV_F_S_APPL_IO, &s->s_flags);
		clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);
		ivtv_release_stream(s);
	}
}