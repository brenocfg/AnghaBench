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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_pgoff; unsigned long vm_end; struct comedi_buf_map* vm_private_data; } ;
struct comedi_buf_map {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int comedi_buf_map_access (struct comedi_buf_map*,unsigned long,void*,int,int) ; 

__attribute__((used)) static int comedi_vm_access(struct vm_area_struct *vma, unsigned long addr,
			    void *buf, int len, int write)
{
	struct comedi_buf_map *bm = vma->vm_private_data;
	unsigned long offset =
	    addr - vma->vm_start + (vma->vm_pgoff << PAGE_SHIFT);

	if (len < 0)
		return -EINVAL;
	if (len > vma->vm_end - addr)
		len = vma->vm_end - addr;
	return comedi_buf_map_access(bm, offset, buf, len, write);
}