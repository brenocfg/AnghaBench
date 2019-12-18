#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u16 ;
struct scsi_target {struct MPT3SAS_TARGET* hostdata; } ;
struct _sas_device {int /*<<< orphan*/  volume_wwid; scalar_t__ volume_handle; struct scsi_target* starget; } ;
struct MPT3SAS_TARGET {int /*<<< orphan*/  flags; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; int /*<<< orphan*/  pd_handles; } ;
struct TYPE_3__ {int /*<<< orphan*/  PhysDiskNum; int /*<<< orphan*/  PhysDiskDevHandle; } ;
typedef  TYPE_1__ Mpi2EventIrConfigElement_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_TARGET_FLAGS_RAID_COMPONENT ; 
 struct _sas_device* __mpt3sas_get_sdev_by_handle (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 int /*<<< orphan*/  _scsih_ir_fastpath (struct MPT3SAS_ADAPTER*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _scsih_reprobe_lun ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt3sas_config_get_volume_handle (struct MPT3SAS_ADAPTER*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  mpt3sas_config_get_volume_wwid (struct MPT3SAS_ADAPTER*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  starget_for_each_device (struct scsi_target*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_sas_pd_hide(struct MPT3SAS_ADAPTER *ioc,
	Mpi2EventIrConfigElement_t *element)
{
	struct _sas_device *sas_device;
	struct scsi_target *starget = NULL;
	struct MPT3SAS_TARGET *sas_target_priv_data;
	unsigned long flags;
	u16 handle = le16_to_cpu(element->PhysDiskDevHandle);
	u16 volume_handle = 0;
	u64 volume_wwid = 0;

	mpt3sas_config_get_volume_handle(ioc, handle, &volume_handle);
	if (volume_handle)
		mpt3sas_config_get_volume_wwid(ioc, volume_handle,
		    &volume_wwid);

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_handle(ioc, handle);
	if (sas_device) {
		set_bit(handle, ioc->pd_handles);
		if (sas_device->starget && sas_device->starget->hostdata) {
			starget = sas_device->starget;
			sas_target_priv_data = starget->hostdata;
			sas_target_priv_data->flags |=
			    MPT_TARGET_FLAGS_RAID_COMPONENT;
			sas_device->volume_handle = volume_handle;
			sas_device->volume_wwid = volume_wwid;
		}
	}
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	if (!sas_device)
		return;

	/* hiding raid component */
	_scsih_ir_fastpath(ioc, handle, element->PhysDiskNum);

	if (starget)
		starget_for_each_device(starget, (void *)1, _scsih_reprobe_lun);

	sas_device_put(sas_device);
}