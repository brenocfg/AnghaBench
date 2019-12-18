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
struct request_queue {struct scsi_device* queuedata; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 scalar_t__ blk_queue_dying (struct request_queue*) ; 
 scalar_t__ scsi_device_is_busy (struct scsi_device*) ; 
 scalar_t__ scsi_host_in_recovery (struct Scsi_Host*) ; 

__attribute__((used)) static bool scsi_mq_lld_busy(struct request_queue *q)
{
	struct scsi_device *sdev = q->queuedata;
	struct Scsi_Host *shost;

	if (blk_queue_dying(q))
		return false;

	shost = sdev->host;

	/*
	 * Ignore host/starget busy state.
	 * Since block layer does not have a concept of fairness across
	 * multiple queues, congestion of host/starget needs to be handled
	 * in SCSI layer.
	 */
	if (scsi_host_in_recovery(shost) || scsi_device_is_busy(sdev))
		return true;

	return false;
}