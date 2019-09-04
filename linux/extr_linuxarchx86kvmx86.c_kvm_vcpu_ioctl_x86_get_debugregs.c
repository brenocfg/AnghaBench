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
struct TYPE_2__ {int /*<<< orphan*/  dr7; int /*<<< orphan*/  db; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_debugregs {unsigned long dr6; int /*<<< orphan*/  reserved; scalar_t__ flags; int /*<<< orphan*/  dr7; int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_get_dr (struct kvm_vcpu*,int,unsigned long*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kvm_vcpu_ioctl_x86_get_debugregs(struct kvm_vcpu *vcpu,
					     struct kvm_debugregs *dbgregs)
{
	unsigned long val;

	memcpy(dbgregs->db, vcpu->arch.db, sizeof(vcpu->arch.db));
	kvm_get_dr(vcpu, 6, &val);
	dbgregs->dr6 = val;
	dbgregs->dr7 = vcpu->arch.dr7;
	dbgregs->flags = 0;
	memset(&dbgregs->reserved, 0, sizeof(dbgregs->reserved));
}