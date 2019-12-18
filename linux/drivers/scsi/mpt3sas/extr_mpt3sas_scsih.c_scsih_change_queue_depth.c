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
struct scsi_device {int /*<<< orphan*/  tagged_supported; struct MPT3SAS_DEVICE* hostdata; struct Scsi_Host* host; } ;
struct _sas_device {int device_info; } ;
struct Scsi_Host {int can_queue; } ;
struct MPT3SAS_TARGET {int flags; } ;
struct MPT3SAS_DEVICE {struct MPT3SAS_TARGET* sas_target; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; scalar_t__ enable_sdev_max_qd; } ;

/* Variables and functions */
 int MPI2_SAS_DEVICE_INFO_SATA_DEVICE ; 
 int MPT3SAS_SATA_QUEUE_DEPTH ; 
 int MPT_TARGET_FLAGS_VOLUME ; 
 struct _sas_device* __mpt3sas_get_sdev_from_target (struct MPT3SAS_ADAPTER*,struct MPT3SAS_TARGET*) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 int scsi_change_queue_depth (struct scsi_device*,int) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
scsih_change_queue_depth(struct scsi_device *sdev, int qdepth)
{
	struct Scsi_Host *shost = sdev->host;
	int max_depth;
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	struct MPT3SAS_DEVICE *sas_device_priv_data;
	struct MPT3SAS_TARGET *sas_target_priv_data;
	struct _sas_device *sas_device;
	unsigned long flags;

	max_depth = shost->can_queue;

	/*
	 * limit max device queue for SATA to 32 if enable_sdev_max_qd
	 * is disabled.
	 */
	if (ioc->enable_sdev_max_qd)
		goto not_sata;

	sas_device_priv_data = sdev->hostdata;
	if (!sas_device_priv_data)
		goto not_sata;
	sas_target_priv_data = sas_device_priv_data->sas_target;
	if (!sas_target_priv_data)
		goto not_sata;
	if ((sas_target_priv_data->flags & MPT_TARGET_FLAGS_VOLUME))
		goto not_sata;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_from_target(ioc, sas_target_priv_data);
	if (sas_device) {
		if (sas_device->device_info & MPI2_SAS_DEVICE_INFO_SATA_DEVICE)
			max_depth = MPT3SAS_SATA_QUEUE_DEPTH;

		sas_device_put(sas_device);
	}
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

 not_sata:

	if (!sdev->tagged_supported)
		max_depth = 1;
	if (qdepth > max_depth)
		qdepth = max_depth;
	return scsi_change_queue_depth(sdev, qdepth);
}