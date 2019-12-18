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
struct visorhba_devdata {int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/  debugfs_info; int /*<<< orphan*/  idr; int /*<<< orphan*/  thread; struct Scsi_Host* scsihost; } ;
struct visor_device {int /*<<< orphan*/  device; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct visorhba_devdata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  visor_thread_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void visorhba_remove(struct visor_device *dev)
{
	struct visorhba_devdata *devdata = dev_get_drvdata(&dev->device);
	struct Scsi_Host *scsihost = NULL;

	if (!devdata)
		return;

	scsihost = devdata->scsihost;
	visor_thread_stop(devdata->thread);
	scsi_remove_host(scsihost);
	scsi_host_put(scsihost);

	idr_destroy(&devdata->idr);

	dev_set_drvdata(&dev->device, NULL);
	debugfs_remove(devdata->debugfs_info);
	debugfs_remove_recursive(devdata->debugfs_dir);
}