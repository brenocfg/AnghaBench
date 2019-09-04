#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ injected; } ;
struct TYPE_4__ {scalar_t__ injected; } ;
struct TYPE_6__ {scalar_t__ nmi_injected; TYPE_2__ interrupt; TYPE_1__ exception; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */

__attribute__((used)) static inline bool kvm_event_needs_reinjection(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.exception.injected || vcpu->arch.interrupt.injected ||
		vcpu->arch.nmi_injected;
}