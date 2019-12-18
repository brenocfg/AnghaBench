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
struct hpsa_scsi_dev_t {int bus; int target; int lun; } ;
struct ctlr_info {int ndevices; struct hpsa_scsi_dev_t** dev; } ;

/* Variables and functions */

__attribute__((used)) static struct hpsa_scsi_dev_t *lookup_hpsa_scsi_dev(struct ctlr_info *h,
	int bus, int target, int lun)
{
	int i;
	struct hpsa_scsi_dev_t *sd;

	for (i = 0; i < h->ndevices; i++) {
		sd = h->dev[i];
		if (sd->bus == bus && sd->target == target && sd->lun == lun)
			return sd;
	}
	return NULL;
}