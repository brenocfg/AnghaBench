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
typedef  int /*<<< orphan*/  u64 ;
struct _sas_device {int /*<<< orphan*/  list; scalar_t__ sas_address; int /*<<< orphan*/  handle; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _scsih_display_enclosure_chassis_info (struct MPT3SAS_ADAPTER*,struct _sas_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
_scsih_sas_device_remove(struct MPT3SAS_ADAPTER *ioc,
	struct _sas_device *sas_device)
{
	unsigned long flags;

	if (!sas_device)
		return;
	ioc_info(ioc, "removing handle(0x%04x), sas_addr(0x%016llx)\n",
		 sas_device->handle, (u64)sas_device->sas_address);

	_scsih_display_enclosure_chassis_info(ioc, sas_device, NULL, NULL);

	/*
	 * The lock serializes access to the list, but we still need to verify
	 * that nobody removed the entry while we were waiting on the lock.
	 */
	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	if (!list_empty(&sas_device->list)) {
		list_del_init(&sas_device->list);
		sas_device_put(sas_device);
	}
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
}