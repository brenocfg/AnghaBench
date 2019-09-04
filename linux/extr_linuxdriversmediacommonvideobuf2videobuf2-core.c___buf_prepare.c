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
struct vb2_queue {int memory; scalar_t__ error; } ;
struct vb2_buffer {unsigned int num_planes; int /*<<< orphan*/  state; TYPE_1__* planes; struct vb2_queue* vb2_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DEQUEUED ; 
 int /*<<< orphan*/  VB2_BUF_STATE_PREPARED ; 
 int /*<<< orphan*/  VB2_BUF_STATE_PREPARING ; 
#define  VB2_MEMORY_DMABUF 130 
#define  VB2_MEMORY_MMAP 129 
#define  VB2_MEMORY_USERPTR 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int __prepare_dmabuf (struct vb2_buffer*,void const*) ; 
 int __prepare_mmap (struct vb2_buffer*,void const*) ; 
 int __prepare_userptr (struct vb2_buffer*,void const*) ; 
 int /*<<< orphan*/  call_void_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  prepare ; 

__attribute__((used)) static int __buf_prepare(struct vb2_buffer *vb, const void *pb)
{
	struct vb2_queue *q = vb->vb2_queue;
	unsigned int plane;
	int ret;

	if (q->error) {
		dprintk(1, "fatal error occurred on queue\n");
		return -EIO;
	}

	vb->state = VB2_BUF_STATE_PREPARING;

	switch (q->memory) {
	case VB2_MEMORY_MMAP:
		ret = __prepare_mmap(vb, pb);
		break;
	case VB2_MEMORY_USERPTR:
		ret = __prepare_userptr(vb, pb);
		break;
	case VB2_MEMORY_DMABUF:
		ret = __prepare_dmabuf(vb, pb);
		break;
	default:
		WARN(1, "Invalid queue type\n");
		ret = -EINVAL;
	}

	if (ret) {
		dprintk(1, "buffer preparation failed: %d\n", ret);
		vb->state = VB2_BUF_STATE_DEQUEUED;
		return ret;
	}

	/* sync buffers */
	for (plane = 0; plane < vb->num_planes; ++plane)
		call_void_memop(vb, prepare, vb->planes[plane].mem_priv);

	vb->state = VB2_BUF_STATE_PREPARED;

	return 0;
}