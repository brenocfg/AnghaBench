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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PAGE_TRACK_WRITE ; 
 int PFERR_PRESENT_MASK ; 
 int PFERR_RSVD_MASK ; 
 int PFERR_WRITE_MASK ; 
 scalar_t__ kvm_page_track_is_active (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool page_fault_handle_page_track(struct kvm_vcpu *vcpu,
					 u32 error_code, gfn_t gfn)
{
	if (unlikely(error_code & PFERR_RSVD_MASK))
		return false;

	if (!(error_code & PFERR_PRESENT_MASK) ||
	      !(error_code & PFERR_WRITE_MASK))
		return false;

	/*
	 * guest is writing the page which is write tracked which can
	 * not be fixed by page fault handler.
	 */
	if (kvm_page_track_is_active(vcpu, gfn, KVM_PAGE_TRACK_WRITE))
		return true;

	return false;
}