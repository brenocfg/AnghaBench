#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  gmap; scalar_t__ sie_page2; int /*<<< orphan*/  dbf; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EVENT (int,char*,struct kvm*) ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  gmap_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_free_vcpus (struct kvm*) ; 
 int /*<<< orphan*/  kvm_is_ucontrol (struct kvm*) ; 
 int /*<<< orphan*/  kvm_s390_clear_float_irqs (struct kvm*) ; 
 int /*<<< orphan*/  kvm_s390_destroy_adapters (struct kvm*) ; 
 int /*<<< orphan*/  kvm_s390_gisa_destroy (struct kvm*) ; 
 int /*<<< orphan*/  kvm_s390_vsie_destroy (struct kvm*) ; 
 int /*<<< orphan*/  sca_dispose (struct kvm*) ; 

void kvm_arch_destroy_vm(struct kvm *kvm)
{
	kvm_free_vcpus(kvm);
	sca_dispose(kvm);
	debug_unregister(kvm->arch.dbf);
	kvm_s390_gisa_destroy(kvm);
	free_page((unsigned long)kvm->arch.sie_page2);
	if (!kvm_is_ucontrol(kvm))
		gmap_remove(kvm->arch.gmap);
	kvm_s390_destroy_adapters(kvm);
	kvm_s390_clear_float_irqs(kvm);
	kvm_s390_vsie_destroy(kvm);
	KVM_EVENT(3, "vm 0x%pK destroyed", kvm);
}