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
struct hpsa_scsi_dev_t {scalar_t__ devtype; scalar_t__ offload_to_be_enabled; int /*<<< orphan*/  offload_enabled; } ;
struct ctlr_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_DISK ; 
 scalar_t__ TYPE_ZBC ; 
 int /*<<< orphan*/  hpsa_figure_phys_disk_ptrs (struct ctlr_info*,struct hpsa_scsi_dev_t**,int,struct hpsa_scsi_dev_t*) ; 
 int /*<<< orphan*/  is_logical_device (struct hpsa_scsi_dev_t*) ; 

__attribute__((used)) static void hpsa_update_log_drive_phys_drive_ptrs(struct ctlr_info *h,
				struct hpsa_scsi_dev_t *dev[], int ndevices)
{
	int i;

	for (i = 0; i < ndevices; i++) {
		if (dev[i] == NULL)
			continue;
		if (dev[i]->devtype != TYPE_DISK &&
		    dev[i]->devtype != TYPE_ZBC)
			continue;
		if (!is_logical_device(dev[i]))
			continue;

		/*
		 * If offload is currently enabled, the RAID map and
		 * phys_disk[] assignment *better* not be changing
		 * because we would be changing ioaccel phsy_disk[] pointers
		 * on a ioaccel volume processing I/O requests.
		 *
		 * If an ioaccel volume status changed, initially because it was
		 * re-configured and thus underwent a transformation, or
		 * a drive failed, we would have received a state change
		 * request and ioaccel should have been turned off. When the
		 * transformation completes, we get another state change
		 * request to turn ioaccel back on. In this case, we need
		 * to update the ioaccel information.
		 *
		 * Thus: If it is not currently enabled, but will be after
		 * the scan completes, make sure the ioaccel pointers
		 * are up to date.
		 */

		if (!dev[i]->offload_enabled && dev[i]->offload_to_be_enabled)
			hpsa_figure_phys_disk_ptrs(h, dev, ndevices, dev[i]);
	}
}