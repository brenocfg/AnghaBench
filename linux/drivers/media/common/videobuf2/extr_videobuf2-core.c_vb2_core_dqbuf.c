#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int /*<<< orphan*/  queued_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  req; } ;
struct vb2_buffer {int state; unsigned int index; int /*<<< orphan*/ * request; TYPE_1__ req_obj; int /*<<< orphan*/  queued_entry; scalar_t__ prepared; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VB2_BUF_STATE_DONE 129 
#define  VB2_BUF_STATE_ERROR 128 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vb2_dqbuf (struct vb2_buffer*) ; 
 int __vb2_get_done_vb (struct vb2_queue*,struct vb2_buffer**,void*,int) ; 
 int /*<<< orphan*/  buf_finish ; 
 int /*<<< orphan*/  call_void_bufop (struct vb2_queue*,int /*<<< orphan*/ ,struct vb2_buffer*,void*) ; 
 int /*<<< orphan*/  call_void_vb_qop (struct vb2_buffer*,int /*<<< orphan*/ ,struct vb2_buffer*) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  fill_user_buffer ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_request_object_put (TYPE_1__*) ; 
 int /*<<< orphan*/  media_request_object_unbind (TYPE_1__*) ; 
 int /*<<< orphan*/  media_request_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_vb2_dqbuf (struct vb2_queue*,struct vb2_buffer*) ; 

int vb2_core_dqbuf(struct vb2_queue *q, unsigned int *pindex, void *pb,
		   bool nonblocking)
{
	struct vb2_buffer *vb = NULL;
	int ret;

	ret = __vb2_get_done_vb(q, &vb, pb, nonblocking);
	if (ret < 0)
		return ret;

	switch (vb->state) {
	case VB2_BUF_STATE_DONE:
		dprintk(3, "returning done buffer\n");
		break;
	case VB2_BUF_STATE_ERROR:
		dprintk(3, "returning done buffer with errors\n");
		break;
	default:
		dprintk(1, "invalid buffer state\n");
		return -EINVAL;
	}

	call_void_vb_qop(vb, buf_finish, vb);
	vb->prepared = 0;

	if (pindex)
		*pindex = vb->index;

	/* Fill buffer information for the userspace */
	if (pb)
		call_void_bufop(q, fill_user_buffer, vb, pb);

	/* Remove from videobuf queue */
	list_del(&vb->queued_entry);
	q->queued_count--;

	trace_vb2_dqbuf(q, vb);

	/* go back to dequeued state */
	__vb2_dqbuf(vb);

	if (WARN_ON(vb->req_obj.req)) {
		media_request_object_unbind(&vb->req_obj);
		media_request_object_put(&vb->req_obj);
	}
	if (vb->request)
		media_request_put(vb->request);
	vb->request = NULL;

	dprintk(2, "dqbuf of buffer %d, with state %d\n",
			vb->index, vb->state);

	return 0;

}