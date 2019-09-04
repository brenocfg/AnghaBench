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
union ctlreg0 {int /*<<< orphan*/  lap; int /*<<< orphan*/  val; } ;
union asce {scalar_t__ p; } ;
struct TYPE_5__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  psw_t ;
struct TYPE_6__ {scalar_t__ dat; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpsw; int /*<<< orphan*/ * gcr; } ;

/* Variables and functions */
 TYPE_3__ psw_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int low_address_protection_enabled(struct kvm_vcpu *vcpu,
					  const union asce asce)
{
	union ctlreg0 ctlreg0 = {.val = vcpu->arch.sie_block->gcr[0]};
	psw_t *psw = &vcpu->arch.sie_block->gpsw;

	if (!ctlreg0.lap)
		return 0;
	if (psw_bits(*psw).dat && asce.p)
		return 0;
	return 1;
}