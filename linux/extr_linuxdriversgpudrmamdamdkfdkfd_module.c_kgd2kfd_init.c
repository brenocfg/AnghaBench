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
struct kgd2kfd_calls {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 unsigned int KFD_INTERFACE_VERSION ; 
 int /*<<< orphan*/  amdkfd_init_completed ; 
 struct kgd2kfd_calls kgd2kfd ; 

int kgd2kfd_init(unsigned int interface_version,
		const struct kgd2kfd_calls **g2f)
{
	if (!amdkfd_init_completed)
		return -EPROBE_DEFER;

	/*
	 * Only one interface version is supported,
	 * no kfd/kgd version skew allowed.
	 */
	if (interface_version != KFD_INTERFACE_VERSION)
		return -EINVAL;

	*g2f = &kgd2kfd;

	return 0;
}