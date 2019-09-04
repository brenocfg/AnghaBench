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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct kvmppc_pte {int raddr; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int HW_PAGE_SIZE ; 
 int INS_DCBZ ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct page* gfn_to_page (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_error_page (struct page*) ; 
 int /*<<< orphan*/ * kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static void kvmppc_patch_dcbz(struct kvm_vcpu *vcpu, struct kvmppc_pte *pte)
{
	struct page *hpage;
	u64 hpage_offset;
	u32 *page;
	int i;

	hpage = gfn_to_page(vcpu->kvm, pte->raddr >> PAGE_SHIFT);
	if (is_error_page(hpage))
		return;

	hpage_offset = pte->raddr & ~PAGE_MASK;
	hpage_offset &= ~0xFFFULL;
	hpage_offset /= 4;

	get_page(hpage);
	page = kmap_atomic(hpage);

	/* patch dcbz into reserved instruction, so we trap */
	for (i=hpage_offset; i < hpage_offset + (HW_PAGE_SIZE / 4); i++)
		if ((be32_to_cpu(page[i]) & 0xff0007ff) == INS_DCBZ)
			page[i] &= cpu_to_be32(0xfffffff7);

	kunmap_atomic(page);
	put_page(hpage);
}