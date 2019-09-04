#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ length; } ;
struct TYPE_4__ {scalar_t__ length; } ;
struct ivtv_stream {scalar_t__ type; TYPE_2__ q_io; TYPE_1__ q_full; int /*<<< orphan*/  waitq; int /*<<< orphan*/  name; int /*<<< orphan*/  s_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  wait; } ;
struct ivtv_open_id {size_t type; TYPE_3__ fh; struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  serialize_lock; struct ivtv_stream* streams; } ;
struct file {int /*<<< orphan*/  private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  IVTV_DEBUG_FILE (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_HI_FILE (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IVTV_ENC_STREAM_TYPE_RAD ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMING ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMOFF ; 
 struct ivtv_open_id* fh2id (int /*<<< orphan*/ ) ; 
 int ivtv_start_capture (struct ivtv_open_id*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int poll_requested_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_event_pending (TYPE_3__*) ; 

__poll_t ivtv_v4l2_enc_poll(struct file *filp, poll_table *wait)
{
	__poll_t req_events = poll_requested_events(wait);
	struct ivtv_open_id *id = fh2id(filp->private_data);
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[id->type];
	int eof = test_bit(IVTV_F_S_STREAMOFF, &s->s_flags);
	__poll_t res = 0;

	/* Start a capture if there is none */
	if (!eof && !test_bit(IVTV_F_S_STREAMING, &s->s_flags) &&
			s->type != IVTV_ENC_STREAM_TYPE_RAD &&
			(req_events & (EPOLLIN | EPOLLRDNORM))) {
		int rc;

		mutex_lock(&itv->serialize_lock);
		rc = ivtv_start_capture(id);
		mutex_unlock(&itv->serialize_lock);
		if (rc) {
			IVTV_DEBUG_INFO("Could not start capture for %s (%d)\n",
					s->name, rc);
			return EPOLLERR;
		}
		IVTV_DEBUG_FILE("Encoder poll started capture\n");
	}

	/* add stream's waitq to the poll list */
	IVTV_DEBUG_HI_FILE("Encoder poll\n");
	poll_wait(filp, &s->waitq, wait);
	if (v4l2_event_pending(&id->fh))
		res |= EPOLLPRI;
	else
		poll_wait(filp, &id->fh.wait, wait);

	if (s->q_full.length || s->q_io.length)
		return res | EPOLLIN | EPOLLRDNORM;
	if (eof)
		return res | EPOLLHUP;
	return res;
}