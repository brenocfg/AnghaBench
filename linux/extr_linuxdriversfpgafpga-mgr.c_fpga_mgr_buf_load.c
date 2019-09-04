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
struct sg_table {int dummy; } ;
struct page {int dummy; } ;
struct fpga_manager {TYPE_1__* mops; } ;
struct fpga_image_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ write; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_SIZE ; 
 int fpga_mgr_buf_load_mapped (struct fpga_manager*,struct fpga_image_info*,char const*,size_t) ; 
 int fpga_mgr_buf_load_sg (struct fpga_manager*,struct fpga_image_info*,struct sg_table*) ; 
 scalar_t__ is_vmalloc_addr (void const*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct page* kmap_to_page (void*) ; 
 char const* offset_in_page (char const*) ; 
 int sg_alloc_table_from_pages (struct sg_table*,struct page**,int,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 struct page* vmalloc_to_page (void const*) ; 

__attribute__((used)) static int fpga_mgr_buf_load(struct fpga_manager *mgr,
			     struct fpga_image_info *info,
			     const char *buf, size_t count)
{
	struct page **pages;
	struct sg_table sgt;
	const void *p;
	int nr_pages;
	int index;
	int rc;

	/*
	 * This is just a fast path if the caller has already created a
	 * contiguous kernel buffer and the driver doesn't require SG, non-SG
	 * drivers will still work on the slow path.
	 */
	if (mgr->mops->write)
		return fpga_mgr_buf_load_mapped(mgr, info, buf, count);

	/*
	 * Convert the linear kernel pointer into a sg_table of pages for use
	 * by the driver.
	 */
	nr_pages = DIV_ROUND_UP((unsigned long)buf + count, PAGE_SIZE) -
		   (unsigned long)buf / PAGE_SIZE;
	pages = kmalloc_array(nr_pages, sizeof(struct page *), GFP_KERNEL);
	if (!pages)
		return -ENOMEM;

	p = buf - offset_in_page(buf);
	for (index = 0; index < nr_pages; index++) {
		if (is_vmalloc_addr(p))
			pages[index] = vmalloc_to_page(p);
		else
			pages[index] = kmap_to_page((void *)p);
		if (!pages[index]) {
			kfree(pages);
			return -EFAULT;
		}
		p += PAGE_SIZE;
	}

	/*
	 * The temporary pages list is used to code share the merging algorithm
	 * in sg_alloc_table_from_pages
	 */
	rc = sg_alloc_table_from_pages(&sgt, pages, index, offset_in_page(buf),
				       count, GFP_KERNEL);
	kfree(pages);
	if (rc)
		return rc;

	rc = fpga_mgr_buf_load_sg(mgr, info, &sgt);
	sg_free_table(&sgt);

	return rc;
}