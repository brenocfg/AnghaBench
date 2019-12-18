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
typedef  int /*<<< orphan*/  u64 ;
struct ivtv_stream {int /*<<< orphan*/  s_flags; int /*<<< orphan*/  name; } ;
struct ivtv_open_id {size_t type; scalar_t__ yuv_frames; struct ivtv* itv; } ;
struct ivtv {scalar_t__ output_mode; int /*<<< orphan*/  i_flags; scalar_t__ speed; struct ivtv_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_FILE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 size_t IVTV_DEC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  IVTV_F_I_DECODING_YUV ; 
 int /*<<< orphan*/  IVTV_F_I_DEC_PAUSED ; 
 int /*<<< orphan*/  IVTV_F_S_APPL_IO ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMING ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMOFF ; 
 void* OUT_NONE ; 
 scalar_t__ OUT_UDMA_YUV ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_release_stream (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_stop_v4l2_decode_stream (struct ivtv_stream*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_yuv_close (struct ivtv*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ivtv_stop_decoding(struct ivtv_open_id *id, int flags, u64 pts)
{
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[id->type];

	IVTV_DEBUG_FILE("close() of %s\n", s->name);

	if (id->type == IVTV_DEC_STREAM_TYPE_YUV &&
		test_bit(IVTV_F_I_DECODING_YUV, &itv->i_flags)) {
		/* Restore registers we've changed & clean up any mess */
		ivtv_yuv_close(itv);
	}

	/* Stop decoding */
	if (test_bit(IVTV_F_S_STREAMING, &s->s_flags)) {
		IVTV_DEBUG_INFO("close stopping decode\n");

		ivtv_stop_v4l2_decode_stream(s, flags, pts);
		itv->output_mode = OUT_NONE;
	}
	clear_bit(IVTV_F_S_APPL_IO, &s->s_flags);
	clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);

	if (itv->output_mode == OUT_UDMA_YUV && id->yuv_frames)
		itv->output_mode = OUT_NONE;

	itv->speed = 0;
	clear_bit(IVTV_F_I_DEC_PAUSED, &itv->i_flags);
	ivtv_release_stream(s);
}