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
struct xen_gem_object {int /*<<< orphan*/  pages; int /*<<< orphan*/  num_pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (size_t,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kvmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gem_alloc_pages_array(struct xen_gem_object *xen_obj,
				 size_t buf_size)
{
	xen_obj->num_pages = DIV_ROUND_UP(buf_size, PAGE_SIZE);
	xen_obj->pages = kvmalloc_array(xen_obj->num_pages,
					sizeof(struct page *), GFP_KERNEL);
	return !xen_obj->pages ? -ENOMEM : 0;
}