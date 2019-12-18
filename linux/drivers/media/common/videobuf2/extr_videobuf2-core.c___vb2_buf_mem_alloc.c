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
struct vb2_queue {int /*<<< orphan*/  gfp_flags; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  dma_attrs; int /*<<< orphan*/  dev; scalar_t__* alloc_devs; } ;
struct vb2_buffer {int num_planes; TYPE_1__* planes; struct vb2_queue* vb2_queue; } ;
struct TYPE_2__ {unsigned long length; int /*<<< orphan*/ * mem_priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  alloc ; 
 void* call_ptr_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_void_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put ; 

__attribute__((used)) static int __vb2_buf_mem_alloc(struct vb2_buffer *vb)
{
	struct vb2_queue *q = vb->vb2_queue;
	void *mem_priv;
	int plane;
	int ret = -ENOMEM;

	/*
	 * Allocate memory for all planes in this buffer
	 * NOTE: mmapped areas should be page aligned
	 */
	for (plane = 0; plane < vb->num_planes; ++plane) {
		/* Memops alloc requires size to be page aligned. */
		unsigned long size = PAGE_ALIGN(vb->planes[plane].length);

		/* Did it wrap around? */
		if (size < vb->planes[plane].length)
			goto free;

		mem_priv = call_ptr_memop(vb, alloc,
				q->alloc_devs[plane] ? : q->dev,
				q->dma_attrs, size, q->dma_dir, q->gfp_flags);
		if (IS_ERR_OR_NULL(mem_priv)) {
			if (mem_priv)
				ret = PTR_ERR(mem_priv);
			goto free;
		}

		/* Associate allocator private data with this plane */
		vb->planes[plane].mem_priv = mem_priv;
	}

	return 0;
free:
	/* Free already allocated memory if one of the allocations failed */
	for (; plane > 0; --plane) {
		call_void_memop(vb, put, vb->planes[plane - 1].mem_priv);
		vb->planes[plane - 1].mem_priv = NULL;
	}

	return ret;
}