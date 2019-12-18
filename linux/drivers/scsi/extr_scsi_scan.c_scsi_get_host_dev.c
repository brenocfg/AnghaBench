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
struct scsi_target {int /*<<< orphan*/  dev; } ;
struct scsi_device {scalar_t__ borken; } ;
struct Scsi_Host {int /*<<< orphan*/  scan_mutex; int /*<<< orphan*/  this_id; int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct scsi_device* scsi_alloc_sdev (struct scsi_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct scsi_target* scsi_alloc_target (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_scan_allowed (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_target_reap (struct scsi_target*) ; 

struct scsi_device *scsi_get_host_dev(struct Scsi_Host *shost)
{
	struct scsi_device *sdev = NULL;
	struct scsi_target *starget;

	mutex_lock(&shost->scan_mutex);
	if (!scsi_host_scan_allowed(shost))
		goto out;
	starget = scsi_alloc_target(&shost->shost_gendev, 0, shost->this_id);
	if (!starget)
		goto out;

	sdev = scsi_alloc_sdev(starget, 0, NULL);
	if (sdev)
		sdev->borken = 0;
	else
		scsi_target_reap(starget);
	put_device(&starget->dev);
 out:
	mutex_unlock(&shost->scan_mutex);
	return sdev;
}