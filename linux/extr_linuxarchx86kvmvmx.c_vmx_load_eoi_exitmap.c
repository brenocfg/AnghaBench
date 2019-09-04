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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOI_EXIT_BITMAP0 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP1 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP2 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP3 ; 
 int /*<<< orphan*/  kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_load_eoi_exitmap(struct kvm_vcpu *vcpu, u64 *eoi_exit_bitmap)
{
	if (!kvm_vcpu_apicv_active(vcpu))
		return;

	vmcs_write64(EOI_EXIT_BITMAP0, eoi_exit_bitmap[0]);
	vmcs_write64(EOI_EXIT_BITMAP1, eoi_exit_bitmap[1]);
	vmcs_write64(EOI_EXIT_BITMAP2, eoi_exit_bitmap[2]);
	vmcs_write64(EOI_EXIT_BITMAP3, eoi_exit_bitmap[3]);
}