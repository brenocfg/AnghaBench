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
struct TYPE_4__ {int /*<<< orphan*/  prefix; int /*<<< orphan*/  stop; int /*<<< orphan*/  extcall; int /*<<< orphan*/  ext; int /*<<< orphan*/  pgm; int /*<<< orphan*/  mchk; } ;
struct kvm_s390_local_interrupt {TYPE_2__ irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  prefix; int /*<<< orphan*/  stop; int /*<<< orphan*/  extcall; int /*<<< orphan*/  ext; int /*<<< orphan*/  pgm; int /*<<< orphan*/  mchk; } ;
struct kvm_s390_irq {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  IRQ_PEND_EXT_CLOCK_COMP 137 
#define  IRQ_PEND_EXT_CPU_TIMER 136 
#define  IRQ_PEND_EXT_EXTERNAL 135 
#define  IRQ_PEND_MCHK_EX 134 
#define  IRQ_PEND_MCHK_REP 133 
#define  IRQ_PEND_PFAULT_INIT 132 
#define  IRQ_PEND_PROG 131 
#define  IRQ_PEND_RESTART 130 
#define  IRQ_PEND_SET_PREFIX 129 
#define  IRQ_PEND_SIGP_STOP 128 
 int /*<<< orphan*/  KVM_S390_INT_CLOCK_COMP ; 
 int /*<<< orphan*/  KVM_S390_INT_CPU_TIMER ; 
 int /*<<< orphan*/  KVM_S390_INT_EXTERNAL_CALL ; 
 int /*<<< orphan*/  KVM_S390_INT_PFAULT_INIT ; 
 int /*<<< orphan*/  KVM_S390_MCHK ; 
 int /*<<< orphan*/  KVM_S390_PROGRAM_INT ; 
 int /*<<< orphan*/  KVM_S390_RESTART ; 
 int /*<<< orphan*/  KVM_S390_SIGP_SET_PREFIX ; 
 int /*<<< orphan*/  KVM_S390_SIGP_STOP ; 

__attribute__((used)) static void store_local_irq(struct kvm_s390_local_interrupt *li,
			    struct kvm_s390_irq *irq,
			    unsigned long irq_type)
{
	switch (irq_type) {
	case IRQ_PEND_MCHK_EX:
	case IRQ_PEND_MCHK_REP:
		irq->type = KVM_S390_MCHK;
		irq->u.mchk = li->irq.mchk;
		break;
	case IRQ_PEND_PROG:
		irq->type = KVM_S390_PROGRAM_INT;
		irq->u.pgm = li->irq.pgm;
		break;
	case IRQ_PEND_PFAULT_INIT:
		irq->type = KVM_S390_INT_PFAULT_INIT;
		irq->u.ext = li->irq.ext;
		break;
	case IRQ_PEND_EXT_EXTERNAL:
		irq->type = KVM_S390_INT_EXTERNAL_CALL;
		irq->u.extcall = li->irq.extcall;
		break;
	case IRQ_PEND_EXT_CLOCK_COMP:
		irq->type = KVM_S390_INT_CLOCK_COMP;
		break;
	case IRQ_PEND_EXT_CPU_TIMER:
		irq->type = KVM_S390_INT_CPU_TIMER;
		break;
	case IRQ_PEND_SIGP_STOP:
		irq->type = KVM_S390_SIGP_STOP;
		irq->u.stop = li->irq.stop;
		break;
	case IRQ_PEND_RESTART:
		irq->type = KVM_S390_RESTART;
		break;
	case IRQ_PEND_SET_PREFIX:
		irq->type = KVM_S390_SIGP_SET_PREFIX;
		irq->u.prefix = li->irq.prefix;
		break;
	}
}