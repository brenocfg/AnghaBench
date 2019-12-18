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
struct hpsa_scsi_dev_t {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct ctlr_info {int /*<<< orphan*/  sas_host; int /*<<< orphan*/  scsi_host; } ;

/* Variables and functions */
 int hpsa_add_sas_device (int /*<<< orphan*/ ,struct hpsa_scsi_dev_t*) ; 
 scalar_t__ is_logical_device (struct hpsa_scsi_dev_t*) ; 
 int scsi_add_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_add_device(struct ctlr_info *h, struct hpsa_scsi_dev_t *device)
{
	int rc = 0;

	if (!h->scsi_host)
		return 1;

	if (is_logical_device(device)) /* RAID */
		rc = scsi_add_device(h->scsi_host, device->bus,
					device->target, device->lun);
	else /* HBA */
		rc = hpsa_add_sas_device(h->sas_host, device);

	return rc;
}