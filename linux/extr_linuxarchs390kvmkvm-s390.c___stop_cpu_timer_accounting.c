#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cputm_start; int /*<<< orphan*/  cputm_seqcount; TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  cputm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ get_tod_clock_fast () ; 
 int /*<<< orphan*/  raw_write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_write_seqcount_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __stop_cpu_timer_accounting(struct kvm_vcpu *vcpu)
{
	WARN_ON_ONCE(vcpu->arch.cputm_start == 0);
	raw_write_seqcount_begin(&vcpu->arch.cputm_seqcount);
	vcpu->arch.sie_block->cputm -= get_tod_clock_fast() - vcpu->arch.cputm_start;
	vcpu->arch.cputm_start = 0;
	raw_write_seqcount_end(&vcpu->arch.cputm_seqcount);
}