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
struct page {int dummy; } ;
struct kvm {int dummy; } ;
typedef  scalar_t__ hpa_t ;
typedef  int gpa_t ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_MASK ; 
 struct page* gfn_to_page (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpa_to_gfn (int) ; 
 scalar_t__ is_error_page (struct page*) ; 
 scalar_t__ page_to_virt (struct page*) ; 

__attribute__((used)) static int pin_guest_page(struct kvm *kvm, gpa_t gpa, hpa_t *hpa)
{
	struct page *page;

	page = gfn_to_page(kvm, gpa_to_gfn(gpa));
	if (is_error_page(page))
		return -EINVAL;
	*hpa = (hpa_t) page_to_virt(page) + (gpa & ~PAGE_MASK);
	return 0;
}