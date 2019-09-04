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
typedef  size_t u32 ;
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int vm_flags; size_t vm_pgoff; } ;
struct usb_usbvision {size_t num_frames; TYPE_1__* frame; int /*<<< orphan*/  max_frame_size; } ;
struct file {int dummy; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MMAP ; 
 int EAGAIN ; 
 int EFAULT ; 
 int EINVAL ; 
 size_t PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 size_t PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  USBVISION_IS_OPERATIONAL (struct usb_usbvision*) ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_WRITE ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 
 scalar_t__ vm_insert_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc_to_page (void*) ; 

__attribute__((used)) static int usbvision_mmap(struct file *file, struct vm_area_struct *vma)
{
	unsigned long size = vma->vm_end - vma->vm_start,
		start = vma->vm_start;
	void *pos;
	u32 i;
	struct usb_usbvision *usbvision = video_drvdata(file);

	PDEBUG(DBG_MMAP, "mmap");

	if (!USBVISION_IS_OPERATIONAL(usbvision))
		return -EFAULT;

	if (!(vma->vm_flags & VM_WRITE) ||
	    size != PAGE_ALIGN(usbvision->max_frame_size)) {
		return -EINVAL;
	}

	for (i = 0; i < usbvision->num_frames; i++) {
		if (((PAGE_ALIGN(usbvision->max_frame_size)*i) >> PAGE_SHIFT) ==
		    vma->vm_pgoff)
			break;
	}
	if (i == usbvision->num_frames) {
		PDEBUG(DBG_MMAP,
		       "mmap: user supplied mapping address is out of range");
		return -EINVAL;
	}

	/* VM_IO is eventually going to replace PageReserved altogether */
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;

	pos = usbvision->frame[i].data;
	while (size > 0) {
		if (vm_insert_page(vma, start, vmalloc_to_page(pos))) {
			PDEBUG(DBG_MMAP, "mmap: vm_insert_page failed");
			return -EAGAIN;
		}
		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		size -= PAGE_SIZE;
	}

	return 0;
}