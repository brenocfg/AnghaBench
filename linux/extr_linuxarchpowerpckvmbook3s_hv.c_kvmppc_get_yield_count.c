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
struct lppaca {int /*<<< orphan*/  yield_count; } ;
struct TYPE_3__ {scalar_t__ pinned_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  vpa_update_lock; TYPE_1__ vpa; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvmppc_get_yield_count(struct kvm_vcpu *vcpu)
{
	int yield_count = 0;
	struct lppaca *lppaca;

	spin_lock(&vcpu->arch.vpa_update_lock);
	lppaca = (struct lppaca *)vcpu->arch.vpa.pinned_addr;
	if (lppaca)
		yield_count = be32_to_cpu(lppaca->yield_count);
	spin_unlock(&vcpu->arch.vpa_update_lock);
	return yield_count;
}