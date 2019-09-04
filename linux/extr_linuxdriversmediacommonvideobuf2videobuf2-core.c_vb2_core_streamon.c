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
struct vb2_queue {unsigned int type; int streaming; scalar_t__ num_buffers; scalar_t__ min_buffers_needed; scalar_t__ queued_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int v4l_vb2q_enable_media_source (struct vb2_queue*) ; 
 int vb2_start_streaming (struct vb2_queue*) ; 

int vb2_core_streamon(struct vb2_queue *q, unsigned int type)
{
	int ret;

	if (type != q->type) {
		dprintk(1, "invalid stream type\n");
		return -EINVAL;
	}

	if (q->streaming) {
		dprintk(3, "already streaming\n");
		return 0;
	}

	if (!q->num_buffers) {
		dprintk(1, "no buffers have been allocated\n");
		return -EINVAL;
	}

	if (q->num_buffers < q->min_buffers_needed) {
		dprintk(1, "need at least %u allocated buffers\n",
				q->min_buffers_needed);
		return -EINVAL;
	}

	/*
	 * Tell driver to start streaming provided sufficient buffers
	 * are available.
	 */
	if (q->queued_count >= q->min_buffers_needed) {
		ret = v4l_vb2q_enable_media_source(q);
		if (ret)
			return ret;
		ret = vb2_start_streaming(q);
		if (ret)
			return ret;
	}

	q->streaming = 1;

	dprintk(3, "successful\n");
	return 0;
}