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
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  XENFEAT_auto_translated_physmap ; 
 int do_remap_pfn (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int,struct page**) ; 
 scalar_t__ xen_feature (int /*<<< orphan*/ ) ; 

int xen_remap_domain_gfn_range(struct vm_area_struct *vma,
			       unsigned long addr,
			       xen_pfn_t gfn, int nr,
			       pgprot_t prot, unsigned domid,
			       struct page **pages)
{
	if (xen_feature(XENFEAT_auto_translated_physmap))
		return -EOPNOTSUPP;

	return do_remap_pfn(vma, addr, &gfn, nr, NULL, prot, domid, false,
			    pages);
}