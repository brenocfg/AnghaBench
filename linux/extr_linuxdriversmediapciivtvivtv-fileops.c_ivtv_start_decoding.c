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
struct ivtv_stream {scalar_t__ type; } ;
struct ivtv_open_id {size_t type; struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  decoding; struct ivtv_stream* streams; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*) ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_MPG ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ ivtv_claim_stream (struct ivtv_open_id*,scalar_t__) ; 
 int ivtv_set_speed (struct ivtv*,int) ; 
 int ivtv_start_v4l2_decode_stream (struct ivtv_stream*,int /*<<< orphan*/ ) ; 

int ivtv_start_decoding(struct ivtv_open_id *id, int speed)
{
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[id->type];
	int rc;

	if (atomic_read(&itv->decoding) == 0) {
		if (ivtv_claim_stream(id, s->type)) {
			/* someone else is using this stream already */
			IVTV_DEBUG_WARN("start decode, stream already claimed\n");
			return -EBUSY;
		}
		rc = ivtv_start_v4l2_decode_stream(s, 0);
		if (rc < 0) {
			if (rc == -EAGAIN)
				rc = ivtv_start_v4l2_decode_stream(s, 0);
			if (rc < 0)
				return rc;
		}
	}
	if (s->type == IVTV_DEC_STREAM_TYPE_MPG)
		return ivtv_set_speed(itv, speed);
	return 0;
}