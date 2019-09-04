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
struct kfd_dev {TYPE_1__* kfd2kgd; } ;
struct TYPE_2__ {int (* alloc_pasid ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* kfd2kgd ; 
 scalar_t__ kfd_topology_enum_kfd_devices (unsigned int,struct kfd_dev**) ; 
 int /*<<< orphan*/  pasid_bits ; 
 int stub1 (int /*<<< orphan*/ ) ; 

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

	r = kfd2kgd->alloc_pasid(pasid_bits);

	return r > 0 ? r : 0;
}