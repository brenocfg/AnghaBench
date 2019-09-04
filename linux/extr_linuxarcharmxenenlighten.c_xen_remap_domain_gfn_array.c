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
typedef  int /*<<< orphan*/  xen_pfn_t ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int xen_xlate_remap_gfn_array (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,unsigned int,struct page**) ; 

int xen_remap_domain_gfn_array(struct vm_area_struct *vma,
			       unsigned long addr,
			       xen_pfn_t *gfn, int nr,
			       int *err_ptr, pgprot_t prot,
			       unsigned domid,
			       struct page **pages)
{
	return xen_xlate_remap_gfn_array(vma, addr, gfn, nr, err_ptr,
					 prot, domid, pages);
}