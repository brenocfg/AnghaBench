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
struct vcpu_svm {int /*<<< orphan*/  vcpu; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ is_error_page (struct page*) ; 
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  kvm_inject_gp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct page* kvm_vcpu_gfn_to_page (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  might_sleep () ; 

__attribute__((used)) static void *nested_svm_map(struct vcpu_svm *svm, u64 gpa, struct page **_page)
{
	struct page *page;

	might_sleep();

	page = kvm_vcpu_gfn_to_page(&svm->vcpu, gpa >> PAGE_SHIFT);
	if (is_error_page(page))
		goto error;

	*_page = page;

	return kmap(page);

error:
	kvm_inject_gp(&svm->vcpu, 0);

	return NULL;
}