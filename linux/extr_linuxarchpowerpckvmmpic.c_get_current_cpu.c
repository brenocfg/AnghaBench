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

__attribute__((used)) static int get_current_cpu(void)
{
#if defined(CONFIG_KVM) && defined(CONFIG_BOOKE)
	struct kvm_vcpu *vcpu = current->thread.kvm_vcpu;
	return vcpu ? vcpu->arch.irq_cpu_id : -1;
#else
	/* XXX */
	return -1;
#endif
}