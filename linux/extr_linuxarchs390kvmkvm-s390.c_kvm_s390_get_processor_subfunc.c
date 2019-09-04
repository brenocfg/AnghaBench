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
struct kvm_device_attr {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static int kvm_s390_get_processor_subfunc(struct kvm *kvm,
					  struct kvm_device_attr *attr)
{
	/*
	 * Once we can actually configure subfunctions (kernel + hw support),
	 * we have to check if they were already set by user space, if so copy
	 * them from kvm->arch.
	 */
	return -ENXIO;
}