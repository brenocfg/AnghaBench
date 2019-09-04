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
struct TYPE_2__ {int /*<<< orphan*/  cpu_feat; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long KVM_S390_VM_CPU_FEAT_NR_BITS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int test_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int test_kvm_cpu_feat(struct kvm *kvm, unsigned long nr)
{
	WARN_ON_ONCE(nr >= KVM_S390_VM_CPU_FEAT_NR_BITS);
	return test_bit_inv(nr, kvm->arch.cpu_feat);
}