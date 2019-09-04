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

/* Variables and functions */
 int /*<<< orphan*/  KVM_FEATURE_PV_EOI ; 
 int /*<<< orphan*/  MSR_KVM_PV_EOI_EN ; 
 int /*<<< orphan*/  kvm_disable_steal_time () ; 
 scalar_t__ kvm_para_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pv_disable_apf () ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_pv_guest_cpu_reboot(void *unused)
{
	/*
	 * We disable PV EOI before we load a new kernel by kexec,
	 * since MSR_KVM_PV_EOI_EN stores a pointer into old kernel's memory.
	 * New kernel can re-enable when it boots.
	 */
	if (kvm_para_has_feature(KVM_FEATURE_PV_EOI))
		wrmsrl(MSR_KVM_PV_EOI_EN, 0);
	kvm_pv_disable_apf();
	kvm_disable_steal_time();
}