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
typedef  int u64 ;
struct TYPE_2__ {unsigned long count_hz; scalar_t__ count_dyn_bias; int /*<<< orphan*/  count_period; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  div_u64 (int,unsigned long) ; 
 int /*<<< orphan*/  kvm_mips_write_count (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_mips_init_count(struct kvm_vcpu *vcpu, unsigned long count_hz)
{
	vcpu->arch.count_hz = count_hz;
	vcpu->arch.count_period = div_u64((u64)NSEC_PER_SEC << 32, count_hz);
	vcpu->arch.count_dyn_bias = 0;

	/* Starting at 0 */
	kvm_mips_write_count(vcpu, 0);
}