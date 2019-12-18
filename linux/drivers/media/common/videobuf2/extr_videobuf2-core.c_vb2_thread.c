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
struct vb2_threadio_data {scalar_t__ stop; int /*<<< orphan*/  priv; scalar_t__ (* fnc ) (struct vb2_buffer*,int /*<<< orphan*/ ) ;} ;
struct vb2_queue {unsigned int num_buffers; int copy_timestamp; struct vb2_buffer** bufs; scalar_t__ is_output; struct vb2_threadio_data* threadio; } ;
struct vb2_buffer {scalar_t__ state; int /*<<< orphan*/  index; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  call_void_qop (struct vb2_queue*,int /*<<< orphan*/ ,struct vb2_queue*) ; 
 int /*<<< orphan*/  dprintk (int,char*,int) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 scalar_t__ stub1 (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int vb2_core_dqbuf (struct vb2_queue*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vb2_core_qbuf (struct vb2_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_finish ; 
 int /*<<< orphan*/  wait_prepare ; 

__attribute__((used)) static int vb2_thread(void *data)
{
	struct vb2_queue *q = data;
	struct vb2_threadio_data *threadio = q->threadio;
	bool copy_timestamp = false;
	unsigned prequeue = 0;
	unsigned index = 0;
	int ret = 0;

	if (q->is_output) {
		prequeue = q->num_buffers;
		copy_timestamp = q->copy_timestamp;
	}

	set_freezable();

	for (;;) {
		struct vb2_buffer *vb;

		/*
		 * Call vb2_dqbuf to get buffer back.
		 */
		if (prequeue) {
			vb = q->bufs[index++];
			prequeue--;
		} else {
			call_void_qop(q, wait_finish, q);
			if (!threadio->stop)
				ret = vb2_core_dqbuf(q, &index, NULL, 0);
			call_void_qop(q, wait_prepare, q);
			dprintk(5, "file io: vb2_dqbuf result: %d\n", ret);
			if (!ret)
				vb = q->bufs[index];
		}
		if (ret || threadio->stop)
			break;
		try_to_freeze();

		if (vb->state != VB2_BUF_STATE_ERROR)
			if (threadio->fnc(vb, threadio->priv))
				break;
		call_void_qop(q, wait_finish, q);
		if (copy_timestamp)
			vb->timestamp = ktime_get_ns();
		if (!threadio->stop)
			ret = vb2_core_qbuf(q, vb->index, NULL, NULL);
		call_void_qop(q, wait_prepare, q);
		if (ret || threadio->stop)
			break;
	}

	/* Hmm, linux becomes *very* unhappy without this ... */
	while (!kthread_should_stop()) {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	}
	return 0;
}