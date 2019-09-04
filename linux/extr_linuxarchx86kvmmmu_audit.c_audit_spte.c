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
 int /*<<< orphan*/  audit_mappings (struct kvm_vcpu*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  audit_spte_after_sync (struct kvm_vcpu*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  audit_sptes_have_rmaps (struct kvm_vcpu*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void audit_spte(struct kvm_vcpu *vcpu, u64 *sptep, int level)
{
	audit_sptes_have_rmaps(vcpu, sptep, level);
	audit_mappings(vcpu, sptep, level);
	audit_spte_after_sync(vcpu, sptep, level);
}