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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {int /*<<< orphan*/  channel; int /*<<< orphan*/  id; TYPE_2__ dev; struct MPT3SAS_TARGET* hostdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  sas_address; } ;
struct sas_rphy {TYPE_1__ identify; } ;
struct _sas_device {scalar_t__ fast_path; int /*<<< orphan*/  handle; int /*<<< orphan*/  channel; int /*<<< orphan*/  id; struct scsi_target* starget; int /*<<< orphan*/  sas_address; } ;
struct _raid_device {struct scsi_target* starget; int /*<<< orphan*/  wwid; int /*<<< orphan*/  handle; } ;
struct _pcie_device {scalar_t__ fast_path; int /*<<< orphan*/  channel; int /*<<< orphan*/  id; struct scsi_target* starget; int /*<<< orphan*/  wwid; int /*<<< orphan*/  handle; } ;
struct Scsi_Host {int dummy; } ;
struct MPT3SAS_TARGET {int /*<<< orphan*/  flags; struct _sas_device* sas_dev; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  handle; struct _pcie_device* pcie_dev; struct _raid_device* raid_device; struct scsi_target* starget; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; int /*<<< orphan*/  pd_handles; int /*<<< orphan*/  pcie_device_lock; int /*<<< orphan*/  raid_device_lock; scalar_t__ is_warpdrive; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MPT3SAS_INVALID_DEVICE_HANDLE ; 
 int /*<<< orphan*/  MPT_TARGET_FASTPATH_IO ; 
 int /*<<< orphan*/  MPT_TARGET_FLAGS_PCIE_DEVICE ; 
 int /*<<< orphan*/  MPT_TARGET_FLAGS_RAID_COMPONENT ; 
 int /*<<< orphan*/  MPT_TARGET_FLAGS_VOLUME ; 
 int /*<<< orphan*/  PCIE_CHANNEL ; 
 int /*<<< orphan*/  RAID_CHANNEL ; 
 struct _pcie_device* __mpt3sas_get_pdev_by_idchannel (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct _sas_device* __mpt3sas_get_sdev_by_addr (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 struct _raid_device* _scsih_raid_device_find_by_id (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sas_rphy* dev_to_rphy (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* dev_to_shost (TYPE_2__*) ; 
 struct MPT3SAS_TARGET* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
scsih_target_alloc(struct scsi_target *starget)
{
	struct Scsi_Host *shost = dev_to_shost(&starget->dev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	struct MPT3SAS_TARGET *sas_target_priv_data;
	struct _sas_device *sas_device;
	struct _raid_device *raid_device;
	struct _pcie_device *pcie_device;
	unsigned long flags;
	struct sas_rphy *rphy;

	sas_target_priv_data = kzalloc(sizeof(*sas_target_priv_data),
				       GFP_KERNEL);
	if (!sas_target_priv_data)
		return -ENOMEM;

	starget->hostdata = sas_target_priv_data;
	sas_target_priv_data->starget = starget;
	sas_target_priv_data->handle = MPT3SAS_INVALID_DEVICE_HANDLE;

	/* RAID volumes */
	if (starget->channel == RAID_CHANNEL) {
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = _scsih_raid_device_find_by_id(ioc, starget->id,
		    starget->channel);
		if (raid_device) {
			sas_target_priv_data->handle = raid_device->handle;
			sas_target_priv_data->sas_address = raid_device->wwid;
			sas_target_priv_data->flags |= MPT_TARGET_FLAGS_VOLUME;
			if (ioc->is_warpdrive)
				sas_target_priv_data->raid_device = raid_device;
			raid_device->starget = starget;
		}
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
		return 0;
	}

	/* PCIe devices */
	if (starget->channel == PCIE_CHANNEL) {
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_by_idchannel(ioc, starget->id,
			starget->channel);
		if (pcie_device) {
			sas_target_priv_data->handle = pcie_device->handle;
			sas_target_priv_data->sas_address = pcie_device->wwid;
			sas_target_priv_data->pcie_dev = pcie_device;
			pcie_device->starget = starget;
			pcie_device->id = starget->id;
			pcie_device->channel = starget->channel;
			sas_target_priv_data->flags |=
				MPT_TARGET_FLAGS_PCIE_DEVICE;
			if (pcie_device->fast_path)
				sas_target_priv_data->flags |=
					MPT_TARGET_FASTPATH_IO;
		}
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		return 0;
	}

	/* sas/sata devices */
	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	rphy = dev_to_rphy(starget->dev.parent);
	sas_device = __mpt3sas_get_sdev_by_addr(ioc,
	   rphy->identify.sas_address);

	if (sas_device) {
		sas_target_priv_data->handle = sas_device->handle;
		sas_target_priv_data->sas_address = sas_device->sas_address;
		sas_target_priv_data->sas_dev = sas_device;
		sas_device->starget = starget;
		sas_device->id = starget->id;
		sas_device->channel = starget->channel;
		if (test_bit(sas_device->handle, ioc->pd_handles))
			sas_target_priv_data->flags |=
			    MPT_TARGET_FLAGS_RAID_COMPONENT;
		if (sas_device->fast_path)
			sas_target_priv_data->flags |=
					MPT_TARGET_FASTPATH_IO;
	}
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	return 0;
}