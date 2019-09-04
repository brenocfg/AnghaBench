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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 scalar_t__ __drop_large_spte (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drop_large_spte(struct kvm_vcpu *vcpu, u64 *sptep)
{
	if (__drop_large_spte(vcpu->kvm, sptep))
		kvm_flush_remote_tlbs(vcpu->kvm);
}