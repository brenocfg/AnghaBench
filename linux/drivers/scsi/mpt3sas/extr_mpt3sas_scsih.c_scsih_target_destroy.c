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
struct scsi_target {scalar_t__ channel; scalar_t__ id; struct MPT3SAS_TARGET* hostdata; int /*<<< orphan*/  dev; } ;
struct _sas_device {scalar_t__ id; scalar_t__ channel; struct scsi_target* starget; } ;
struct _raid_device {int /*<<< orphan*/ * sdev; int /*<<< orphan*/ * starget; } ;
struct _pcie_device {scalar_t__ id; scalar_t__ channel; struct scsi_target* starget; } ;
struct Scsi_Host {int dummy; } ;
struct MPT3SAS_TARGET {int /*<<< orphan*/ * sas_dev; int /*<<< orphan*/ * pcie_dev; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; int /*<<< orphan*/  pcie_device_lock; int /*<<< orphan*/  raid_device_lock; } ;

/* Variables and functions */
 scalar_t__ PCIE_CHANNEL ; 
 scalar_t__ RAID_CHANNEL ; 
 struct _pcie_device* __mpt3sas_get_pdev_from_target (struct MPT3SAS_ADAPTER*,struct MPT3SAS_TARGET*) ; 
 struct _sas_device* __mpt3sas_get_sdev_from_target (struct MPT3SAS_ADAPTER*,struct MPT3SAS_TARGET*) ; 
 struct _raid_device* _scsih_raid_device_find_by_id (struct MPT3SAS_ADAPTER*,scalar_t__,scalar_t__) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct MPT3SAS_TARGET*) ; 
 int /*<<< orphan*/  pcie_device_put (struct _pcie_device*) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
scsih_target_destroy(struct scsi_target *starget)
{
	struct Scsi_Host *shost = dev_to_shost(&starget->dev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	struct MPT3SAS_TARGET *sas_target_priv_data;
	struct _sas_device *sas_device;
	struct _raid_device *raid_device;
	struct _pcie_device *pcie_device;
	unsigned long flags;

	sas_target_priv_data = starget->hostdata;
	if (!sas_target_priv_data)
		return;

	if (starget->channel == RAID_CHANNEL) {
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = _scsih_raid_device_find_by_id(ioc, starget->id,
		    starget->channel);
		if (raid_device) {
			raid_device->starget = NULL;
			raid_device->sdev = NULL;
		}
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
		goto out;
	}

	if (starget->channel == PCIE_CHANNEL) {
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_from_target(ioc,
							sas_target_priv_data);
		if (pcie_device && (pcie_device->starget == starget) &&
			(pcie_device->id == starget->id) &&
			(pcie_device->channel == starget->channel))
			pcie_device->starget = NULL;

		if (pcie_device) {
			/*
			 * Corresponding get() is in _scsih_target_alloc()
			 */
			sas_target_priv_data->pcie_dev = NULL;
			pcie_device_put(pcie_device);
			pcie_device_put(pcie_device);
		}
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		goto out;
	}

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_from_target(ioc, sas_target_priv_data);
	if (sas_device && (sas_device->starget == starget) &&
	    (sas_device->id == starget->id) &&
	    (sas_device->channel == starget->channel))
		sas_device->starget = NULL;

	if (sas_device) {
		/*
		 * Corresponding get() is in _scsih_target_alloc()
		 */
		sas_target_priv_data->sas_dev = NULL;
		sas_device_put(sas_device);

		sas_device_put(sas_device);
	}
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

 out:
	kfree(sas_target_priv_data);
	starget->hostdata = NULL;
}