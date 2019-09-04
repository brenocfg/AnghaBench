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
struct TYPE_2__ {int /*<<< orphan*/  sint; int /*<<< orphan*/  vcpu; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ hv_sint; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int kvm_hv_synic_set_irq (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_hv_set_sint(struct kvm_kernel_irq_routing_entry *e,
		    struct kvm *kvm, int irq_source_id, int level,
		    bool line_status)
{
	if (!level)
		return -1;

	return kvm_hv_synic_set_irq(kvm, e->hv_sint.vcpu, e->hv_sint.sint);
}