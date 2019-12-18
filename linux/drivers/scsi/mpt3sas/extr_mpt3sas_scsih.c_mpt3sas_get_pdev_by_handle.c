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
typedef  int /*<<< orphan*/  u16 ;
struct _pcie_device {int dummy; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  pcie_device_lock; } ;

/* Variables and functions */
 struct _pcie_device* __mpt3sas_get_pdev_by_handle (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct _pcie_device *
mpt3sas_get_pdev_by_handle(struct MPT3SAS_ADAPTER *ioc, u16 handle)
{
	struct _pcie_device *pcie_device;
	unsigned long flags;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	pcie_device = __mpt3sas_get_pdev_by_handle(ioc, handle);
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	return pcie_device;
}