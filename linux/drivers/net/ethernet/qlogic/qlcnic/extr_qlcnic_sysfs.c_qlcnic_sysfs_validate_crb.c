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
struct qlcnic_adapter {int flags; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 scalar_t__ ADDR_IN_RANGE (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int QLCNIC_DIAG_ENABLED ; 
 int /*<<< orphan*/  QLCNIC_PCI_CAMQM ; 
 int /*<<< orphan*/  QLCNIC_PCI_CAMQM_END ; 
 size_t QLCNIC_PCI_CRBSPACE ; 

__attribute__((used)) static int qlcnic_sysfs_validate_crb(struct qlcnic_adapter *adapter,
				     loff_t offset, size_t size)
{
	size_t crb_size = 4;

	if (!(adapter->flags & QLCNIC_DIAG_ENABLED))
		return -EIO;

	if (offset < QLCNIC_PCI_CRBSPACE) {
		if (ADDR_IN_RANGE(offset, QLCNIC_PCI_CAMQM,
				  QLCNIC_PCI_CAMQM_END))
			crb_size = 8;
		else
			return -EINVAL;
	}

	if ((size != crb_size) || (offset & (crb_size-1)))
		return  -EINVAL;

	return 0;
}