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
struct vm_area_struct {int vm_pgoff; int vm_flags; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct videobuf_mapping* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct videobuf_queue {struct videobuf_buffer** bufs; } ;
struct videobuf_mapping {int count; struct videobuf_queue* q; } ;
struct videobuf_dma_sg_memory {int /*<<< orphan*/  magic; } ;
struct videobuf_buffer {int /*<<< orphan*/  bsize; scalar_t__ baddr; struct videobuf_mapping* map; struct videobuf_dma_sg_memory* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_SG_MEM ; 
 unsigned int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 unsigned int VIDEO_MAX_FRAME ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 struct videobuf_mapping* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videobuf_vm_ops ; 

__attribute__((used)) static int __videobuf_mmap_mapper(struct videobuf_queue *q,
				  struct videobuf_buffer *buf,
				  struct vm_area_struct *vma)
{
	struct videobuf_dma_sg_memory *mem = buf->priv;
	struct videobuf_mapping *map;
	unsigned int first, last, size = 0, i;
	int retval;

	retval = -EINVAL;

	BUG_ON(!mem);
	MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);

	/* look for first buffer to map */
	for (first = 0; first < VIDEO_MAX_FRAME; first++) {
		if (buf == q->bufs[first]) {
			size = PAGE_ALIGN(q->bufs[first]->bsize);
			break;
		}
	}

	/* paranoia, should never happen since buf is always valid. */
	if (!size) {
		dprintk(1, "mmap app bug: offset invalid [offset=0x%lx]\n",
				(vma->vm_pgoff << PAGE_SHIFT));
		goto done;
	}

	last = first;

	/* create mapping + update buffer list */
	retval = -ENOMEM;
	map = kmalloc(sizeof(struct videobuf_mapping), GFP_KERNEL);
	if (NULL == map)
		goto done;

	size = 0;
	for (i = first; i <= last; i++) {
		if (NULL == q->bufs[i])
			continue;
		q->bufs[i]->map   = map;
		q->bufs[i]->baddr = vma->vm_start + size;
		size += PAGE_ALIGN(q->bufs[i]->bsize);
	}

	map->count    = 1;
	map->q        = q;
	vma->vm_ops   = &videobuf_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_flags &= ~VM_IO; /* using shared anonymous pages */
	vma->vm_private_data = map;
	dprintk(1, "mmap %p: q=%p %08lx-%08lx pgoff %08lx bufs %d-%d\n",
		map, q, vma->vm_start, vma->vm_end, vma->vm_pgoff, first, last);
	retval = 0;

done:
	return retval;
}