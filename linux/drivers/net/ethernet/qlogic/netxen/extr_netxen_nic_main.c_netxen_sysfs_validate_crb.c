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
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {int flags; TYPE_1__ ahw; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 scalar_t__ ADDR_IN_RANGE (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int NETXEN_NIC_DIAG_ENABLED ; 
 int /*<<< orphan*/  NETXEN_PCI_CAMQM ; 
 int /*<<< orphan*/  NETXEN_PCI_CAMQM_2M_END ; 
 size_t NETXEN_PCI_CRBSPACE ; 
 scalar_t__ NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netxen_sysfs_validate_crb(struct netxen_adapter *adapter,
		loff_t offset, size_t size)
{
	size_t crb_size = 4;

	if (!(adapter->flags & NETXEN_NIC_DIAG_ENABLED))
		return -EIO;

	if (offset < NETXEN_PCI_CRBSPACE) {
		if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
			return -EINVAL;

		if (ADDR_IN_RANGE(offset, NETXEN_PCI_CAMQM,
						NETXEN_PCI_CAMQM_2M_END))
			crb_size = 8;
		else
			return -EINVAL;
	}

	if ((size != crb_size) || (offset & (crb_size-1)))
		return  -EINVAL;

	return 0;
}