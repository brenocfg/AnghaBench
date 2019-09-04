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
typedef  scalar_t__ u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ kvm_scale_tsc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtsc () ; 

__attribute__((used)) static u64 kvm_compute_tsc_offset(struct kvm_vcpu *vcpu, u64 target_tsc)
{
	u64 tsc;

	tsc = kvm_scale_tsc(vcpu, rdtsc());

	return target_tsc - tsc;
}