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
typedef  int /*<<< orphan*/  u8 ;
struct kvm_s390_local_interrupt {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct kvm_s390_local_interrupt local_int; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int SIGP_CC_BUSY ; 
 scalar_t__ kvm_s390_is_stop_irq_pending (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __prepare_sigp_re_start(struct kvm_vcpu *vcpu,
				   struct kvm_vcpu *dst_vcpu, u8 order_code)
{
	struct kvm_s390_local_interrupt *li = &dst_vcpu->arch.local_int;
	/* handle (RE)START in user space */
	int rc = -EOPNOTSUPP;

	/* make sure we don't race with STOP irq injection */
	spin_lock(&li->lock);
	if (kvm_s390_is_stop_irq_pending(dst_vcpu))
		rc = SIGP_CC_BUSY;
	spin_unlock(&li->lock);

	return rc;
}