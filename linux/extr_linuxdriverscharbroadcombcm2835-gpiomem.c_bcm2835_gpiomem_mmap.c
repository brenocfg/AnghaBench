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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_start; int /*<<< orphan*/ * vm_ops; } ;
struct file {int dummy; } ;
struct TYPE_2__ {unsigned long gpio_regs_phys; } ;

/* Variables and functions */
 int EAGAIN ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bcm2835_gpiomem_vm_ops ; 
 TYPE_1__* inst ; 
 int /*<<< orphan*/  phys_mem_access_prot (struct file*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835_gpiomem_mmap(struct file *file, struct vm_area_struct *vma)
{
	/* Ignore what the user says - they're getting the GPIO regs
	   whether they like it or not! */
	unsigned long gpio_page = inst->gpio_regs_phys >> PAGE_SHIFT;

	vma->vm_page_prot = phys_mem_access_prot(file, gpio_page,
						 PAGE_SIZE,
						 vma->vm_page_prot);
	vma->vm_ops = &bcm2835_gpiomem_vm_ops;
	if (remap_pfn_range(vma, vma->vm_start,
			gpio_page,
			PAGE_SIZE,
			vma->vm_page_prot)) {
		return -EAGAIN;
	}
	return 0;
}