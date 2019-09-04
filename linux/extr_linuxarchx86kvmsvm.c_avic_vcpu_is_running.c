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
struct vcpu_svm {int /*<<< orphan*/ * avic_physical_id_cache; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool avic_vcpu_is_running(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	u64 *entry = svm->avic_physical_id_cache;

	if (!entry)
		return false;

	return (READ_ONCE(*entry) & AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK);
}