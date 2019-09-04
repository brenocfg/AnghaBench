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
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  depth; } ;
struct cx18_stream {scalar_t__ vb_type; TYPE_1__ q_full; int /*<<< orphan*/  waitq; int /*<<< orphan*/  vbuf_q; int /*<<< orphan*/  name; int /*<<< orphan*/  s_flags; } ;
struct cx18_open_id {size_t type; int /*<<< orphan*/  fh; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  serialize_lock; struct cx18_stream* streams; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_FILE (char*) ; 
 int /*<<< orphan*/  CX18_DEBUG_HI_FILE (char*) ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,int /*<<< orphan*/ ,int) ; 
 size_t CX18_ENC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int /*<<< orphan*/  CX18_F_S_STREAMOFF ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int cx18_start_capture (struct cx18_open_id*) ; 
 struct cx18_open_id* file2id (struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int poll_requested_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_event_pending (int /*<<< orphan*/ *) ; 
 int videobuf_poll_stream (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__poll_t cx18_v4l2_enc_poll(struct file *filp, poll_table *wait)
{
	__poll_t req_events = poll_requested_events(wait);
	struct cx18_open_id *id = file2id(filp);
	struct cx18 *cx = id->cx;
	struct cx18_stream *s = &cx->streams[id->type];
	int eof = test_bit(CX18_F_S_STREAMOFF, &s->s_flags);
	__poll_t res = 0;

	/* Start a capture if there is none */
	if (!eof && !test_bit(CX18_F_S_STREAMING, &s->s_flags) &&
			(req_events & (EPOLLIN | EPOLLRDNORM))) {
		int rc;

		mutex_lock(&cx->serialize_lock);
		rc = cx18_start_capture(id);
		mutex_unlock(&cx->serialize_lock);
		if (rc) {
			CX18_DEBUG_INFO("Could not start capture for %s (%d)\n",
					s->name, rc);
			return EPOLLERR;
		}
		CX18_DEBUG_FILE("Encoder poll started capture\n");
	}

	if ((s->vb_type == V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		(id->type == CX18_ENC_STREAM_TYPE_YUV)) {
		__poll_t videobuf_poll = videobuf_poll_stream(filp, &s->vbuf_q, wait);

		if (v4l2_event_pending(&id->fh))
			res |= EPOLLPRI;
		if (eof && videobuf_poll == EPOLLERR)
			return res | EPOLLHUP;
		return res | videobuf_poll;
	}

	/* add stream's waitq to the poll list */
	CX18_DEBUG_HI_FILE("Encoder poll\n");
	if (v4l2_event_pending(&id->fh))
		res |= EPOLLPRI;
	else
		poll_wait(filp, &s->waitq, wait);

	if (atomic_read(&s->q_full.depth))
		return res | EPOLLIN | EPOLLRDNORM;
	if (eof)
		return res | EPOLLHUP;
	return res;
}