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
struct pci_dev {int devfn; TYPE_2__* sriov; TYPE_1__* bus; int /*<<< orphan*/  is_physfn; } ;
struct TYPE_4__ {int offset; int stride; } ;
struct TYPE_3__ {int number; } ;

/* Variables and functions */
 int EINVAL ; 

int pci_iov_virtfn_bus(struct pci_dev *dev, int vf_id)
{
	if (!dev->is_physfn)
		return -EINVAL;
	return dev->bus->number + ((dev->devfn + dev->sriov->offset +
				    dev->sriov->stride * vf_id) >> 8);
}