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
typedef  size_t u32 ;
struct page {int dummy; } ;
struct kvm_vcpu_hv_synic {int msg_page; } ;
struct kvm_vcpu {int dummy; } ;
struct hv_message_page {struct hv_message* sint_message; } ;
struct TYPE_4__ {int msg_pending; } ;
struct TYPE_6__ {int /*<<< orphan*/  payload_size; int /*<<< orphan*/  message_type; TYPE_1__ message_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  payload; } ;
struct hv_message {TYPE_3__ header; TYPE_2__ u; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int ENOENT ; 
 scalar_t__ HVMSG_NONE ; 
 int HV_SYNIC_SIMP_ENABLE ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 scalar_t__ is_error_page (struct page*) ; 
 struct hv_message_page* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (struct hv_message_page*) ; 
 int /*<<< orphan*/  kvm_release_page_dirty (struct page*) ; 
 struct page* kvm_vcpu_gfn_to_page (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_vcpu_mark_page_dirty (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sync_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int synic_set_irq (struct kvm_vcpu_hv_synic*,size_t) ; 
 struct kvm_vcpu* synic_to_vcpu (struct kvm_vcpu_hv_synic*) ; 

__attribute__((used)) static int synic_deliver_msg(struct kvm_vcpu_hv_synic *synic, u32 sint,
			     struct hv_message *src_msg)
{
	struct kvm_vcpu *vcpu = synic_to_vcpu(synic);
	struct page *page;
	gpa_t gpa;
	struct hv_message *dst_msg;
	int r;
	struct hv_message_page *msg_page;

	if (!(synic->msg_page & HV_SYNIC_SIMP_ENABLE))
		return -ENOENT;

	gpa = synic->msg_page & PAGE_MASK;
	page = kvm_vcpu_gfn_to_page(vcpu, gpa >> PAGE_SHIFT);
	if (is_error_page(page))
		return -EFAULT;

	msg_page = kmap_atomic(page);
	dst_msg = &msg_page->sint_message[sint];
	if (sync_cmpxchg(&dst_msg->header.message_type, HVMSG_NONE,
			 src_msg->header.message_type) != HVMSG_NONE) {
		dst_msg->header.message_flags.msg_pending = 1;
		r = -EAGAIN;
	} else {
		memcpy(&dst_msg->u.payload, &src_msg->u.payload,
		       src_msg->header.payload_size);
		dst_msg->header.message_type = src_msg->header.message_type;
		dst_msg->header.payload_size = src_msg->header.payload_size;
		r = synic_set_irq(synic, sint);
		if (r >= 1)
			r = 0;
		else if (r == 0)
			r = -EFAULT;
	}
	kunmap_atomic(msg_page);
	kvm_release_page_dirty(page);
	kvm_vcpu_mark_page_dirty(vcpu, gpa >> PAGE_SHIFT);
	return r;
}