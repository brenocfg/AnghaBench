#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long prefix; scalar_t__ mso; } ;
struct vsie_page {TYPE_3__ scb_s; int /*<<< orphan*/  gmap; } ;
struct page {struct kvm* private; } ;
struct TYPE_4__ {int page_count; int /*<<< orphan*/ * pages; } ;
struct TYPE_5__ {TYPE_1__ vsie; } ;
struct kvm {TYPE_2__ arch; } ;
struct gmap {struct kvm* private; } ;

/* Variables and functions */
 unsigned long GUEST_PREFIX_SHIFT ; 
 int PAGE_SIZE ; 
 struct page* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct page*) ; 
 struct vsie_page* page_to_virt (struct page*) ; 
 int /*<<< orphan*/  prefix_unmapped_sync (struct vsie_page*) ; 

void kvm_s390_vsie_gmap_notifier(struct gmap *gmap, unsigned long start,
				 unsigned long end)
{
	struct kvm *kvm = gmap->private;
	struct vsie_page *cur;
	unsigned long prefix;
	struct page *page;
	int i;

	if (!gmap_is_shadow(gmap))
		return;
	if (start >= 1UL << 31)
		/* We are only interested in prefix pages */
		return;

	/*
	 * Only new shadow blocks are added to the list during runtime,
	 * therefore we can safely reference them all the time.
	 */
	for (i = 0; i < kvm->arch.vsie.page_count; i++) {
		page = READ_ONCE(kvm->arch.vsie.pages[i]);
		if (!page)
			continue;
		cur = page_to_virt(page);
		if (READ_ONCE(cur->gmap) != gmap)
			continue;
		prefix = cur->scb_s.prefix << GUEST_PREFIX_SHIFT;
		/* with mso/msl, the prefix lies at an offset */
		prefix += cur->scb_s.mso;
		if (prefix <= end && start <= prefix + 2 * PAGE_SIZE - 1)
			prefix_unmapped_sync(cur);
	}
}