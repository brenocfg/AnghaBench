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
struct vb2_queue {unsigned int num_buffers; int /*<<< orphan*/  queued_list; int /*<<< orphan*/  memory; struct vb2_buffer** bufs; } ;
struct vb2_buffer {scalar_t__ state; TYPE_1__* planes; } ;
struct TYPE_2__ {scalar_t__ mem_priv; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ VB2_BUF_STATE_PREPARING ; 
 int /*<<< orphan*/  VB2_MEMORY_UNKNOWN ; 
 int /*<<< orphan*/  __vb2_free_mem (struct vb2_queue*,unsigned int) ; 
 int /*<<< orphan*/  buf_cleanup ; 
 int /*<<< orphan*/  call_void_vb_qop (struct vb2_buffer*,int /*<<< orphan*/ ,struct vb2_buffer*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  kfree (struct vb2_buffer*) ; 

__attribute__((used)) static int __vb2_queue_free(struct vb2_queue *q, unsigned int buffers)
{
	unsigned int buffer;

	/*
	 * Sanity check: when preparing a buffer the queue lock is released for
	 * a short while (see __buf_prepare for the details), which would allow
	 * a race with a reqbufs which can call this function. Removing the
	 * buffers from underneath __buf_prepare is obviously a bad idea, so we
	 * check if any of the buffers is in the state PREPARING, and if so we
	 * just return -EAGAIN.
	 */
	for (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) {
		if (q->bufs[buffer] == NULL)
			continue;
		if (q->bufs[buffer]->state == VB2_BUF_STATE_PREPARING) {
			dprintk(1, "preparing buffers, cannot free\n");
			return -EAGAIN;
		}
	}

	/* Call driver-provided cleanup function for each buffer, if provided */
	for (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) {
		struct vb2_buffer *vb = q->bufs[buffer];

		if (vb && vb->planes[0].mem_priv)
			call_void_vb_qop(vb, buf_cleanup, vb);
	}

	/* Release video buffer memory */
	__vb2_free_mem(q, buffers);

#ifdef CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Check that all the calls were balances during the life-time of this
	 * queue. If not (or if the debug level is 1 or up), then dump the
	 * counters to the kernel log.
	 */
	if (q->num_buffers) {
		bool unbalanced = q->cnt_start_streaming != q->cnt_stop_streaming ||
				  q->cnt_wait_prepare != q->cnt_wait_finish;

		if (unbalanced || debug) {
			pr_info("counters for queue %p:%s\n", q,
				unbalanced ? " UNBALANCED!" : "");
			pr_info("     setup: %u start_streaming: %u stop_streaming: %u\n",
				q->cnt_queue_setup, q->cnt_start_streaming,
				q->cnt_stop_streaming);
			pr_info("     wait_prepare: %u wait_finish: %u\n",
				q->cnt_wait_prepare, q->cnt_wait_finish);
		}
		q->cnt_queue_setup = 0;
		q->cnt_wait_prepare = 0;
		q->cnt_wait_finish = 0;
		q->cnt_start_streaming = 0;
		q->cnt_stop_streaming = 0;
	}
	for (buffer = 0; buffer < q->num_buffers; ++buffer) {
		struct vb2_buffer *vb = q->bufs[buffer];
		bool unbalanced = vb->cnt_mem_alloc != vb->cnt_mem_put ||
				  vb->cnt_mem_prepare != vb->cnt_mem_finish ||
				  vb->cnt_mem_get_userptr != vb->cnt_mem_put_userptr ||
				  vb->cnt_mem_attach_dmabuf != vb->cnt_mem_detach_dmabuf ||
				  vb->cnt_mem_map_dmabuf != vb->cnt_mem_unmap_dmabuf ||
				  vb->cnt_buf_queue != vb->cnt_buf_done ||
				  vb->cnt_buf_prepare != vb->cnt_buf_finish ||
				  vb->cnt_buf_init != vb->cnt_buf_cleanup;

		if (unbalanced || debug) {
			pr_info("   counters for queue %p, buffer %d:%s\n",
				q, buffer, unbalanced ? " UNBALANCED!" : "");
			pr_info("     buf_init: %u buf_cleanup: %u buf_prepare: %u buf_finish: %u\n",
				vb->cnt_buf_init, vb->cnt_buf_cleanup,
				vb->cnt_buf_prepare, vb->cnt_buf_finish);
			pr_info("     buf_queue: %u buf_done: %u\n",
				vb->cnt_buf_queue, vb->cnt_buf_done);
			pr_info("     alloc: %u put: %u prepare: %u finish: %u mmap: %u\n",
				vb->cnt_mem_alloc, vb->cnt_mem_put,
				vb->cnt_mem_prepare, vb->cnt_mem_finish,
				vb->cnt_mem_mmap);
			pr_info("     get_userptr: %u put_userptr: %u\n",
				vb->cnt_mem_get_userptr, vb->cnt_mem_put_userptr);
			pr_info("     attach_dmabuf: %u detach_dmabuf: %u map_dmabuf: %u unmap_dmabuf: %u\n",
				vb->cnt_mem_attach_dmabuf, vb->cnt_mem_detach_dmabuf,
				vb->cnt_mem_map_dmabuf, vb->cnt_mem_unmap_dmabuf);
			pr_info("     get_dmabuf: %u num_users: %u vaddr: %u cookie: %u\n",
				vb->cnt_mem_get_dmabuf,
				vb->cnt_mem_num_users,
				vb->cnt_mem_vaddr,
				vb->cnt_mem_cookie);
		}
	}
#endif

	/* Free videobuf buffers */
	for (buffer = q->num_buffers - buffers; buffer < q->num_buffers;
	     ++buffer) {
		kfree(q->bufs[buffer]);
		q->bufs[buffer] = NULL;
	}

	q->num_buffers -= buffers;
	if (!q->num_buffers) {
		q->memory = VB2_MEMORY_UNKNOWN;
		INIT_LIST_HEAD(&q->queued_list);
	}
	return 0;
}