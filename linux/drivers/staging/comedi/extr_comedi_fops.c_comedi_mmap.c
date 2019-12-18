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
struct vm_area_struct {unsigned long vm_start; int vm_flags; scalar_t__ vm_pgoff; unsigned long vm_end; TYPE_1__* vm_ops; struct comedi_buf_map* vm_private_data; } ;
struct file {struct comedi_file* private_data; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_file {struct comedi_device* dev; } ;
struct comedi_device {int /*<<< orphan*/  attach_lock; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  attached; } ;
struct comedi_buf_page {int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  dma_addr; } ;
struct comedi_buf_map {int n_pages; scalar_t__ dma_dir; struct comedi_buf_page* page_list; int /*<<< orphan*/  dma_hw_dev; } ;
struct comedi_async {unsigned long prealloc_bufsz; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* open ) (struct vm_area_struct*) ;} ;

/* Variables and functions */
 scalar_t__ DMA_NONE ; 
 int EAGAIN ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 int PAGE_SIZE ; 
 int VM_WRITE ; 
 struct comedi_buf_map* comedi_buf_map_from_subdev_get (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  comedi_buf_map_put (struct comedi_buf_map*) ; 
 struct comedi_subdevice* comedi_file_read_subdevice (struct file*) ; 
 struct comedi_subdevice* comedi_file_write_subdevice (struct file*) ; 
 TYPE_1__ comedi_vm_ops ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int dma_mmap_coherent (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ offset_in_page (unsigned long) ; 
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 
 int remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vm_area_struct*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 
 int vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static int comedi_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct comedi_file *cfp = file->private_data;
	struct comedi_device *dev = cfp->dev;
	struct comedi_subdevice *s;
	struct comedi_async *async;
	struct comedi_buf_map *bm = NULL;
	struct comedi_buf_page *buf;
	unsigned long start = vma->vm_start;
	unsigned long size;
	int n_pages;
	int i;
	int retval = 0;

	/*
	 * 'trylock' avoids circular dependency with current->mm->mmap_sem
	 * and down-reading &dev->attach_lock should normally succeed without
	 * contention unless the device is in the process of being attached
	 * or detached.
	 */
	if (!down_read_trylock(&dev->attach_lock))
		return -EAGAIN;

	if (!dev->attached) {
		dev_dbg(dev->class_dev, "no driver attached\n");
		retval = -ENODEV;
		goto done;
	}

	if (vma->vm_flags & VM_WRITE)
		s = comedi_file_write_subdevice(file);
	else
		s = comedi_file_read_subdevice(file);
	if (!s) {
		retval = -EINVAL;
		goto done;
	}

	async = s->async;
	if (!async) {
		retval = -EINVAL;
		goto done;
	}

	if (vma->vm_pgoff != 0) {
		dev_dbg(dev->class_dev, "mmap() offset must be 0.\n");
		retval = -EINVAL;
		goto done;
	}

	size = vma->vm_end - vma->vm_start;
	if (size > async->prealloc_bufsz) {
		retval = -EFAULT;
		goto done;
	}
	if (offset_in_page(size)) {
		retval = -EFAULT;
		goto done;
	}

	n_pages = vma_pages(vma);

	/* get reference to current buf map (if any) */
	bm = comedi_buf_map_from_subdev_get(s);
	if (!bm || n_pages > bm->n_pages) {
		retval = -EINVAL;
		goto done;
	}
	if (bm->dma_dir != DMA_NONE) {
		/*
		 * DMA buffer was allocated as a single block.
		 * Address is in page_list[0].
		 */
		buf = &bm->page_list[0];
		retval = dma_mmap_coherent(bm->dma_hw_dev, vma, buf->virt_addr,
					   buf->dma_addr, n_pages * PAGE_SIZE);
	} else {
		for (i = 0; i < n_pages; ++i) {
			unsigned long pfn;

			buf = &bm->page_list[i];
			pfn = page_to_pfn(virt_to_page(buf->virt_addr));
			retval = remap_pfn_range(vma, start, pfn, PAGE_SIZE,
						 PAGE_SHARED);
			if (retval)
				break;

			start += PAGE_SIZE;
		}
	}

	if (retval == 0) {
		vma->vm_ops = &comedi_vm_ops;
		vma->vm_private_data = bm;

		vma->vm_ops->open(vma);
	}

done:
	up_read(&dev->attach_lock);
	comedi_buf_map_put(bm);	/* put reference to buf map - okay if NULL */
	return retval;
}