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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KVM_DEV_TYPE_FLIC ; 
 int /*<<< orphan*/  debug_register (char*,int,int,int) ; 
 scalar_t__ debug_register_view (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_sprintf_view ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_flic_ops ; 
 int kvm_register_device_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_cpu_feat_init () ; 
 int /*<<< orphan*/  kvm_s390_dbf ; 

int kvm_arch_init(void *opaque)
{
	kvm_s390_dbf = debug_register("kvm-trace", 32, 1, 7 * sizeof(long));
	if (!kvm_s390_dbf)
		return -ENOMEM;

	if (debug_register_view(kvm_s390_dbf, &debug_sprintf_view)) {
		debug_unregister(kvm_s390_dbf);
		return -ENOMEM;
	}

	kvm_s390_cpu_feat_init();

	/* Register floating interrupt controller interface. */
	return kvm_register_device_ops(&kvm_flic_ops, KVM_DEV_TYPE_FLIC);
}