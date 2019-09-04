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
struct vm_area_struct {unsigned long vm_pgoff; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_start; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long CAC_ADDR (unsigned long) ; 
 unsigned long DMA_ATTR_WRITE_COMBINE ; 
 int ENXIO ; 
 unsigned long PAGE_ALIGN (size_t) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_is_coherent (struct device*) ; 
 scalar_t__ dma_mmap_from_dev_coherent (struct device*,struct vm_area_struct*,void*,size_t,int*) ; 
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int remap_pfn_range (struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 
 unsigned long vma_pages (struct vm_area_struct*) ; 

int arch_dma_mmap(struct device *dev, struct vm_area_struct *vma,
		void *cpu_addr, dma_addr_t dma_addr, size_t size,
		unsigned long attrs)
{
	unsigned long user_count = vma_pages(vma);
	unsigned long count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	unsigned long addr = (unsigned long)cpu_addr;
	unsigned long off = vma->vm_pgoff;
	unsigned long pfn;
	int ret = -ENXIO;

	if (!dev_is_coherent(dev))
		addr = CAC_ADDR(addr);

	pfn = page_to_pfn(virt_to_page((void *)addr));

	if (attrs & DMA_ATTR_WRITE_COMBINE)
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	else
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	if (dma_mmap_from_dev_coherent(dev, vma, cpu_addr, size, &ret))
		return ret;

	if (off < count && user_count <= (count - off)) {
		ret = remap_pfn_range(vma, vma->vm_start,
				      pfn + off,
				      user_count << PAGE_SHIFT,
				      vma->vm_page_prot);
	}

	return ret;
}