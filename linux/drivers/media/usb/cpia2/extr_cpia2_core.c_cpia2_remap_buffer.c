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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; unsigned long vm_pgoff; } ;
struct camera_data {unsigned long frame_size; unsigned long num_frames; int mmapped; scalar_t__ frame_buffer; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned long,unsigned long) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long kvirt_to_pa (unsigned long) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_is_registered (int /*<<< orphan*/ *) ; 

int cpia2_remap_buffer(struct camera_data *cam, struct vm_area_struct *vma)
{
	const char *adr = (const char *)vma->vm_start;
	unsigned long size = vma->vm_end-vma->vm_start;
	unsigned long start_offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long start = (unsigned long) adr;
	unsigned long page, pos;

	DBG("mmap offset:%ld size:%ld\n", start_offset, size);

	if (!video_is_registered(&cam->vdev))
		return -ENODEV;

	if (size > cam->frame_size*cam->num_frames  ||
	    (start_offset % cam->frame_size) != 0 ||
	    (start_offset+size > cam->frame_size*cam->num_frames))
		return -EINVAL;

	pos = ((unsigned long) (cam->frame_buffer)) + start_offset;
	while (size > 0) {
		page = kvirt_to_pa(pos);
		if (remap_pfn_range(vma, start, page >> PAGE_SHIFT, PAGE_SIZE, PAGE_SHARED))
			return -EAGAIN;
		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		if (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		else
			size = 0;
	}

	cam->mmapped = true;
	return 0;
}