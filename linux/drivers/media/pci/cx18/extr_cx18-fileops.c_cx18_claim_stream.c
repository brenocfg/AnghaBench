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
struct cx18_stream {int id; int /*<<< orphan*/  s_flags; } ;
struct cx18_open_id {int open_id; struct cx18* cx; } ;
struct TYPE_2__ {scalar_t__ insert_mpeg; } ;
struct cx18 {struct cx18_stream* streams; TYPE_1__ vbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,...) ; 
 int CX18_ENC_STREAM_TYPE_IDX ; 
 int CX18_ENC_STREAM_TYPE_MPG ; 
 int CX18_ENC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  CX18_F_S_CLAIMED ; 
 int /*<<< orphan*/  CX18_F_S_INTERNAL_USE ; 
 int /*<<< orphan*/  CX18_WARN (char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  cx18_raw_vbi (struct cx18*) ; 
 int /*<<< orphan*/  cx18_stream_enabled (struct cx18_stream*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cx18_claim_stream(struct cx18_open_id *id, int type)
{
	struct cx18 *cx = id->cx;
	struct cx18_stream *s = &cx->streams[type];
	struct cx18_stream *s_assoc;

	/* Nothing should ever try to directly claim the IDX stream */
	if (type == CX18_ENC_STREAM_TYPE_IDX) {
		CX18_WARN("MPEG Index stream cannot be claimed directly, but something tried.\n");
		return -EINVAL;
	}

	if (test_and_set_bit(CX18_F_S_CLAIMED, &s->s_flags)) {
		/* someone already claimed this stream */
		if (s->id == id->open_id) {
			/* yes, this file descriptor did. So that's OK. */
			return 0;
		}
		if (s->id == -1 && type == CX18_ENC_STREAM_TYPE_VBI) {
			/* VBI is handled already internally, now also assign
			   the file descriptor to this stream for external
			   reading of the stream. */
			s->id = id->open_id;
			CX18_DEBUG_INFO("Start Read VBI\n");
			return 0;
		}
		/* someone else is using this stream already */
		CX18_DEBUG_INFO("Stream %d is busy\n", type);
		return -EBUSY;
	}
	s->id = id->open_id;

	/*
	 * CX18_ENC_STREAM_TYPE_MPG needs to claim:
	 * CX18_ENC_STREAM_TYPE_VBI, if VBI insertion is on for sliced VBI, or
	 * CX18_ENC_STREAM_TYPE_IDX, if VBI insertion is off for sliced VBI
	 * (We don't yet fix up MPEG Index entries for our inserted packets).
	 *
	 * For all other streams we're done.
	 */
	if (type != CX18_ENC_STREAM_TYPE_MPG)
		return 0;

	s_assoc = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
	if (cx->vbi.insert_mpeg && !cx18_raw_vbi(cx))
		s_assoc = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
	else if (!cx18_stream_enabled(s_assoc))
		return 0;

	set_bit(CX18_F_S_CLAIMED, &s_assoc->s_flags);

	/* mark that it is used internally */
	set_bit(CX18_F_S_INTERNAL_USE, &s_assoc->s_flags);
	return 0;
}