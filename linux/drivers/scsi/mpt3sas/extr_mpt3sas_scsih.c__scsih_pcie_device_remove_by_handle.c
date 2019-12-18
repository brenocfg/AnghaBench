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
struct _pcie_device {int /*<<< orphan*/  list; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  pcie_device_lock; scalar_t__ shost_recovery; } ;

/* Variables and functions */
 struct _pcie_device* __mpt3sas_get_pdev_by_handle (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _scsih_pcie_device_remove_from_sml (struct MPT3SAS_ADAPTER*,struct _pcie_device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_device_put (struct _pcie_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
_scsih_pcie_device_remove_by_handle(struct MPT3SAS_ADAPTER *ioc, u16 handle)
{
	struct _pcie_device *pcie_device;
	unsigned long flags;
	int was_on_pcie_device_list = 0;

	if (ioc->shost_recovery)
		return;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	pcie_device = __mpt3sas_get_pdev_by_handle(ioc, handle);
	if (pcie_device) {
		if (!list_empty(&pcie_device->list)) {
			list_del_init(&pcie_device->list);
			was_on_pcie_device_list = 1;
			pcie_device_put(pcie_device);
		}
	}
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
	if (was_on_pcie_device_list) {
		_scsih_pcie_device_remove_from_sml(ioc, pcie_device);
		pcie_device_put(pcie_device);
	}
}