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
struct kvm_hpt_info {int order; scalar_t__ virt; scalar_t__ cma; int /*<<< orphan*/ * rev; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  free_pages (scalar_t__,int) ; 
 int /*<<< orphan*/  kvm_free_hpt_cma (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 

void kvmppc_free_hpt(struct kvm_hpt_info *info)
{
	vfree(info->rev);
	info->rev = NULL;
	if (info->cma)
		kvm_free_hpt_cma(virt_to_page(info->virt),
				 1 << (info->order - PAGE_SHIFT));
	else if (info->virt)
		free_pages(info->virt, info->order - PAGE_SHIFT);
	info->virt = 0;
	info->order = 0;
}