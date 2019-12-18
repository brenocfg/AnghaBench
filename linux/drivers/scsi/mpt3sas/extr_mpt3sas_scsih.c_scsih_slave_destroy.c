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
struct scsi_target {int /*<<< orphan*/  dev; struct MPT3SAS_TARGET* hostdata; } ;
struct scsi_device {int /*<<< orphan*/ * hostdata; } ;
struct _sas_device {int /*<<< orphan*/ * starget; } ;
struct _pcie_device {int /*<<< orphan*/ * starget; } ;
struct Scsi_Host {int dummy; } ;
struct MPT3SAS_TARGET {int flags; int /*<<< orphan*/  num_luns; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; int /*<<< orphan*/  pcie_device_lock; } ;

/* Variables and functions */
 int MPT_TARGET_FLAGS_PCIE_DEVICE ; 
 int MPT_TARGET_FLAGS_VOLUME ; 
 struct _pcie_device* __mpt3sas_get_pdev_from_target (struct MPT3SAS_ADAPTER*,struct MPT3SAS_TARGET*) ; 
 struct _sas_device* __mpt3sas_get_sdev_from_target (struct MPT3SAS_ADAPTER*,struct MPT3SAS_TARGET*) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_device_put (struct _pcie_device*) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
scsih_slave_destroy(struct scsi_device *sdev)
{
	struct MPT3SAS_TARGET *sas_target_priv_data;
	struct scsi_target *starget;
	struct Scsi_Host *shost;
	struct MPT3SAS_ADAPTER *ioc;
	struct _sas_device *sas_device;
	struct _pcie_device *pcie_device;
	unsigned long flags;

	if (!sdev->hostdata)
		return;

	starget = scsi_target(sdev);
	sas_target_priv_data = starget->hostdata;
	sas_target_priv_data->num_luns--;

	shost = dev_to_shost(&starget->dev);
	ioc = shost_priv(shost);

	if (sas_target_priv_data->flags & MPT_TARGET_FLAGS_PCIE_DEVICE) {
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_from_target(ioc,
				sas_target_priv_data);
		if (pcie_device && !sas_target_priv_data->num_luns)
			pcie_device->starget = NULL;

		if (pcie_device)
			pcie_device_put(pcie_device);

		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	} else if (!(sas_target_priv_data->flags & MPT_TARGET_FLAGS_VOLUME)) {
		spin_lock_irqsave(&ioc->sas_device_lock, flags);
		sas_device = __mpt3sas_get_sdev_from_target(ioc,
				sas_target_priv_data);
		if (sas_device && !sas_target_priv_data->num_luns)
			sas_device->starget = NULL;

		if (sas_device)
			sas_device_put(sas_device);
		spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	}

	kfree(sdev->hostdata);
	sdev->hostdata = NULL;
}