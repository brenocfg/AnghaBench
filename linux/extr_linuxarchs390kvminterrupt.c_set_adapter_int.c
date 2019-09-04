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
struct s390_io_adapter {int /*<<< orphan*/  masked; int /*<<< orphan*/  maps_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter_id; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ adapter; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int adapter_indicators_set (struct kvm*,struct s390_io_adapter*,TYPE_1__*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct s390_io_adapter* get_io_adapter (struct kvm*,int /*<<< orphan*/ ) ; 
 int kvm_s390_inject_airq (struct kvm*,struct s390_io_adapter*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_adapter_int(struct kvm_kernel_irq_routing_entry *e,
			   struct kvm *kvm, int irq_source_id, int level,
			   bool line_status)
{
	int ret;
	struct s390_io_adapter *adapter;

	/* We're only interested in the 0->1 transition. */
	if (!level)
		return 0;
	adapter = get_io_adapter(kvm, e->adapter.adapter_id);
	if (!adapter)
		return -1;
	down_read(&adapter->maps_lock);
	ret = adapter_indicators_set(kvm, adapter, &e->adapter);
	up_read(&adapter->maps_lock);
	if ((ret > 0) && !adapter->masked) {
		ret = kvm_s390_inject_airq(kvm, adapter);
		if (ret == 0)
			ret = 1;
	}
	return ret;
}