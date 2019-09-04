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
struct vm_area_struct {int vm_flags; int vm_pgoff; } ;
struct videobuf_queue {struct videobuf_buffer** bufs; TYPE_1__* int_ops; } ;
struct videobuf_buffer {scalar_t__ memory; int boff; } ;
struct TYPE_2__ {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int CALL (struct videobuf_queue*,int /*<<< orphan*/ ,struct videobuf_queue*,struct videobuf_buffer*,struct vm_area_struct*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_QTYPE_OPS ; 
 int PAGE_SHIFT ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int VIDEO_MAX_FRAME ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  mmap_mapper ; 
 int /*<<< orphan*/  videobuf_queue_lock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_queue_unlock (struct videobuf_queue*) ; 

int videobuf_mmap_mapper(struct videobuf_queue *q, struct vm_area_struct *vma)
{
	int rc = -EINVAL;
	int i;

	MAGIC_CHECK(q->int_ops->magic, MAGIC_QTYPE_OPS);

	if (!(vma->vm_flags & VM_WRITE) || !(vma->vm_flags & VM_SHARED)) {
		dprintk(1, "mmap appl bug: PROT_WRITE and MAP_SHARED are required\n");
		return -EINVAL;
	}

	videobuf_queue_lock(q);
	for (i = 0; i < VIDEO_MAX_FRAME; i++) {
		struct videobuf_buffer *buf = q->bufs[i];

		if (buf && buf->memory == V4L2_MEMORY_MMAP &&
				buf->boff == (vma->vm_pgoff << PAGE_SHIFT)) {
			rc = CALL(q, mmap_mapper, q, buf, vma);
			break;
		}
	}
	videobuf_queue_unlock(q);

	return rc;
}