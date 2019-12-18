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
struct videobuf_dmabuf {int direction; unsigned long offset; unsigned long size; unsigned long nr_pages; int /*<<< orphan*/ * pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int FOLL_FORCE ; 
 unsigned int FOLL_LONGTERM ; 
 unsigned int FOLL_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int READ ; 
 int WRITE ; 
 int /*<<< orphan*/  dprintk (int,char*,int,int,...) ; 
 int get_user_pages (unsigned long,unsigned long,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int videobuf_dma_init_user_locked(struct videobuf_dmabuf *dma,
			int direction, unsigned long data, unsigned long size)
{
	unsigned long first, last;
	int err, rw = 0;
	unsigned int flags = FOLL_FORCE;

	dma->direction = direction;
	switch (dma->direction) {
	case DMA_FROM_DEVICE:
		rw = READ;
		break;
	case DMA_TO_DEVICE:
		rw = WRITE;
		break;
	default:
		BUG();
	}

	first = (data          & PAGE_MASK) >> PAGE_SHIFT;
	last  = ((data+size-1) & PAGE_MASK) >> PAGE_SHIFT;
	dma->offset = data & ~PAGE_MASK;
	dma->size = size;
	dma->nr_pages = last-first+1;
	dma->pages = kmalloc_array(dma->nr_pages, sizeof(struct page *),
				   GFP_KERNEL);
	if (NULL == dma->pages)
		return -ENOMEM;

	if (rw == READ)
		flags |= FOLL_WRITE;

	dprintk(1, "init user [0x%lx+0x%lx => %d pages]\n",
		data, size, dma->nr_pages);

	err = get_user_pages(data & PAGE_MASK, dma->nr_pages,
			     flags | FOLL_LONGTERM, dma->pages, NULL);

	if (err != dma->nr_pages) {
		dma->nr_pages = (err >= 0) ? err : 0;
		dprintk(1, "get_user_pages: err=%d [%d]\n", err,
			dma->nr_pages);
		return err < 0 ? err : -EINVAL;
	}
	return 0;
}