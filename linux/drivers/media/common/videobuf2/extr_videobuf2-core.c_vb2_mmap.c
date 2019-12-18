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
struct vm_area_struct {unsigned long vm_pgoff; int vm_flags; unsigned long vm_end; unsigned long vm_start; } ;
struct vb2_queue {scalar_t__ memory; int /*<<< orphan*/  mmap_lock; struct vb2_buffer** bufs; scalar_t__ is_output; } ;
struct vb2_buffer {TYPE_1__* planes; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem_priv; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned long PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ VB2_MEMORY_MMAP ; 
 int VM_READ ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int __find_plane_by_offset (struct vb2_queue*,unsigned long,unsigned int*,unsigned int*) ; 
 int call_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  mmap ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vb2_fileio_is_active (struct vb2_queue*) ; 

int vb2_mmap(struct vb2_queue *q, struct vm_area_struct *vma)
{
	unsigned long off = vma->vm_pgoff << PAGE_SHIFT;
	struct vb2_buffer *vb;
	unsigned int buffer = 0, plane = 0;
	int ret;
	unsigned long length;

	if (q->memory != VB2_MEMORY_MMAP) {
		dprintk(1, "queue is not currently set up for mmap\n");
		return -EINVAL;
	}

	/*
	 * Check memory area access mode.
	 */
	if (!(vma->vm_flags & VM_SHARED)) {
		dprintk(1, "invalid vma flags, VM_SHARED needed\n");
		return -EINVAL;
	}
	if (q->is_output) {
		if (!(vma->vm_flags & VM_WRITE)) {
			dprintk(1, "invalid vma flags, VM_WRITE needed\n");
			return -EINVAL;
		}
	} else {
		if (!(vma->vm_flags & VM_READ)) {
			dprintk(1, "invalid vma flags, VM_READ needed\n");
			return -EINVAL;
		}
	}

	mutex_lock(&q->mmap_lock);

	if (vb2_fileio_is_active(q)) {
		dprintk(1, "mmap: file io in progress\n");
		ret = -EBUSY;
		goto unlock;
	}

	/*
	 * Find the plane corresponding to the offset passed by userspace.
	 */
	ret = __find_plane_by_offset(q, off, &buffer, &plane);
	if (ret)
		goto unlock;

	vb = q->bufs[buffer];

	/*
	 * MMAP requires page_aligned buffers.
	 * The buffer length was page_aligned at __vb2_buf_mem_alloc(),
	 * so, we need to do the same here.
	 */
	length = PAGE_ALIGN(vb->planes[plane].length);
	if (length < (vma->vm_end - vma->vm_start)) {
		dprintk(1,
			"MMAP invalid, as it would overflow buffer length\n");
		ret = -EINVAL;
		goto unlock;
	}

	/*
	 * vm_pgoff is treated in V4L2 API as a 'cookie' to select a buffer,
	 * not as a in-buffer offset. We always want to mmap a whole buffer
	 * from its beginning.
	 */
	vma->vm_pgoff = 0;

	ret = call_memop(vb, mmap, vb->planes[plane].mem_priv, vma);

unlock:
	mutex_unlock(&q->mmap_lock);
	if (ret)
		return ret;

	dprintk(3, "buffer %d, plane %d successfully mapped\n", buffer, plane);
	return 0;
}