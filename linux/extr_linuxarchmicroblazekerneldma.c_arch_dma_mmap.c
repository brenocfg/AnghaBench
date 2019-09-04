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
struct vm_area_struct {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENXIO ; 

int arch_dma_mmap(struct device *dev, struct vm_area_struct *vma,
		void *cpu_addr, dma_addr_t handle, size_t size,
		unsigned long attrs)
{
#ifdef CONFIG_MMU
	unsigned long user_count = vma_pages(vma);
	unsigned long count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	unsigned long off = vma->vm_pgoff;
	unsigned long pfn;

	if (off >= count || user_count > (count - off))
		return -ENXIO;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	pfn = consistent_virt_to_pfn(cpu_addr);
	return remap_pfn_range(vma, vma->vm_start, pfn + off,
			       vma->vm_end - vma->vm_start, vma->vm_page_prot);
#else
	return -ENXIO;
#endif
}