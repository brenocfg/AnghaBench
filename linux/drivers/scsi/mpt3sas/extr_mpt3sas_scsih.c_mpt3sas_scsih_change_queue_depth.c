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
struct scsi_device {struct Scsi_Host* host; } ;
struct Scsi_Host {int can_queue; } ;
struct MPT3SAS_ADAPTER {scalar_t__ enable_sdev_max_qd; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsih_change_queue_depth (struct scsi_device*,int) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 

void
mpt3sas_scsih_change_queue_depth(struct scsi_device *sdev, int qdepth)
{
	struct Scsi_Host *shost = sdev->host;
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	if (ioc->enable_sdev_max_qd)
		qdepth = shost->can_queue;

	scsih_change_queue_depth(sdev, qdepth);
}