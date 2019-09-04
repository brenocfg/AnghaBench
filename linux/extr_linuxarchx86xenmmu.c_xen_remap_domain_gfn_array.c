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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XENFEAT_auto_translated_physmap ; 
 int do_remap_pfn (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,unsigned int,int,struct page**) ; 
 scalar_t__ xen_feature (int /*<<< orphan*/ ) ; 
 int xen_xlate_remap_gfn_array (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,unsigned int,struct page**) ; 

int xen_remap_domain_gfn_array(struct vm_area_struct *vma,
			       unsigned long addr,
			       xen_pfn_t *gfn, int nr,
			       int *err_ptr, pgprot_t prot,
			       unsigned domid, struct page **pages)
{
	if (xen_feature(XENFEAT_auto_translated_physmap))
		return xen_xlate_remap_gfn_array(vma, addr, gfn, nr, err_ptr,
						 prot, domid, pages);

	/* We BUG_ON because it's a programmer error to pass a NULL err_ptr,
	 * and the consequences later is quite hard to detect what the actual
	 * cause of "wrong memory was mapped in".
	 */
	BUG_ON(err_ptr == NULL);
	return do_remap_pfn(vma, addr, gfn, nr, err_ptr, prot, domid,
			    false, pages);
}