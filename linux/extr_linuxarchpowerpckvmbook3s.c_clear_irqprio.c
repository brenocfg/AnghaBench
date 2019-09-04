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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
#define  BOOK3S_IRQPRIO_DECREMENTER 129 
#define  BOOK3S_IRQPRIO_EXTERNAL_LEVEL 128 

__attribute__((used)) static bool clear_irqprio(struct kvm_vcpu *vcpu, unsigned int priority)
{
	switch (priority) {
		case BOOK3S_IRQPRIO_DECREMENTER:
			/* DEC interrupts get cleared by mtdec */
			return false;
		case BOOK3S_IRQPRIO_EXTERNAL_LEVEL:
			/* External interrupts get cleared by userspace */
			return false;
	}

	return true;
}