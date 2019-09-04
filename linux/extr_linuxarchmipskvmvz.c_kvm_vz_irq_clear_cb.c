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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pending_exceptions_clr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
#define  MIPS_EXC_INT_IO 131 
#define  MIPS_EXC_INT_IPI_1 130 
#define  MIPS_EXC_INT_IPI_2 129 
#define  MIPS_EXC_INT_TIMER 128 
 unsigned int MIPS_EXC_MAX ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_c0_guestctl2 (int) ; 
 int /*<<< orphan*/  clear_gc0_cause (int) ; 
 int /*<<< orphan*/  cpu_has_guestctl2 ; 
 int* kvm_vz_priority_to_irq ; 
 int read_c0_guestctl2 () ; 

__attribute__((used)) static int kvm_vz_irq_clear_cb(struct kvm_vcpu *vcpu, unsigned int priority,
			       u32 cause)
{
	u32 irq = (priority < MIPS_EXC_MAX) ?
		kvm_vz_priority_to_irq[priority] : 0;

	switch (priority) {
	case MIPS_EXC_INT_TIMER:
		/*
		 * Call to kvm_write_c0_guest_compare() clears Cause.TI in
		 * kvm_mips_emulate_CP0(). Explicitly clear irq associated with
		 * Cause.IP[IPTI] if GuestCtl2 virtual interrupt register not
		 * supported or if not using GuestCtl2 Hardware Clear.
		 */
		if (cpu_has_guestctl2) {
			if (!(read_c0_guestctl2() & (irq << 14)))
				clear_c0_guestctl2(irq);
		} else {
			clear_gc0_cause(irq);
		}
		break;

	case MIPS_EXC_INT_IO:
	case MIPS_EXC_INT_IPI_1:
	case MIPS_EXC_INT_IPI_2:
		/* Clear GuestCtl2.VIP irq if not using Hardware Clear */
		if (cpu_has_guestctl2) {
			if (!(read_c0_guestctl2() & (irq << 14)))
				clear_c0_guestctl2(irq);
		} else {
			clear_gc0_cause(irq);
		}
		break;

	default:
		break;
	}

	clear_bit(priority, &vcpu->arch.pending_exceptions_clr);
	return 1;
}