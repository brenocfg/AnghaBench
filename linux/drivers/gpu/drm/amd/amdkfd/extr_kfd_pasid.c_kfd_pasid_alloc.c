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
struct kfd_dev {scalar_t__ kfd2kgd; } ;

/* Variables and functions */
 int amdgpu_pasid_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ kfd2kgd ; 
 scalar_t__ kfd_topology_enum_kfd_devices (unsigned int,struct kfd_dev**) ; 
 int /*<<< orphan*/  pasid_bits ; 

unsigned int kfd_pasid_alloc(void)
{
	int r;

	/* Find the first best KFD device for calling KGD */
	if (!kfd2kgd) {
		struct kfd_dev *dev = NULL;
		unsigned int i = 0;

		while ((kfd_topology_enum_kfd_devices(i, &dev)) == 0) {
			if (dev && dev->kfd2kgd) {
				kfd2kgd = dev->kfd2kgd;
				break;
			}
			i++;
		}

		if (!kfd2kgd)
			return false;
	}

	r = amdgpu_pasid_alloc(pasid_bits);

	return r > 0 ? r : 0;
}