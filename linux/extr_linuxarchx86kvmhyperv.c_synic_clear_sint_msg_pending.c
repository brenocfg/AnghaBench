#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct page {int dummy; } ;
struct kvm_vcpu_hv_synic {int msg_page; } ;
struct kvm_vcpu {int dummy; } ;
struct hv_message_page {struct hv_message* sint_message; } ;
struct TYPE_3__ {scalar_t__ msg_pending; } ;
struct TYPE_4__ {TYPE_1__ message_flags; } ;
struct hv_message {TYPE_2__ header; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 scalar_t__ is_error_page (struct page*) ; 
 struct hv_message_page* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (struct hv_message_page*) ; 
 int /*<<< orphan*/  kvm_release_page_dirty (struct page*) ; 
 struct page* kvm_vcpu_gfn_to_page (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_vcpu_mark_page_dirty (struct kvm_vcpu*,int) ; 
 struct kvm_vcpu* synic_to_vcpu (struct kvm_vcpu_hv_synic*) ; 
 int /*<<< orphan*/  vcpu_err (struct kvm_vcpu*,char*,int) ; 

__attribute__((used)) static void synic_clear_sint_msg_pending(struct kvm_vcpu_hv_synic *synic,
					u32 sint)
{
	struct kvm_vcpu *vcpu = synic_to_vcpu(synic);
	struct page *page;
	gpa_t gpa;
	struct hv_message *msg;
	struct hv_message_page *msg_page;

	gpa = synic->msg_page & PAGE_MASK;
	page = kvm_vcpu_gfn_to_page(vcpu, gpa >> PAGE_SHIFT);
	if (is_error_page(page)) {
		vcpu_err(vcpu, "Hyper-V SynIC can't get msg page, gpa 0x%llx\n",
			 gpa);
		return;
	}
	msg_page = kmap_atomic(page);

	msg = &msg_page->sint_message[sint];
	msg->header.message_flags.msg_pending = 0;

	kunmap_atomic(msg_page);
	kvm_release_page_dirty(page);
	kvm_vcpu_mark_page_dirty(vcpu, gpa >> PAGE_SHIFT);
}