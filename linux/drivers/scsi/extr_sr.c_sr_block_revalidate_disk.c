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
struct scsi_sense_hdr {int dummy; } ;
struct scsi_cd {int /*<<< orphan*/  cdi; int /*<<< orphan*/  device; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 int /*<<< orphan*/  SR_TIMEOUT ; 
 int /*<<< orphan*/  get_sectorsize (struct scsi_cd*) ; 
 struct scsi_cd* scsi_cd_get (struct gendisk*) ; 
 int /*<<< orphan*/  scsi_cd_put (struct scsi_cd*) ; 
 scalar_t__ scsi_test_unit_ready (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sr_cd_check (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sr_block_revalidate_disk(struct gendisk *disk)
{
	struct scsi_sense_hdr sshdr;
	struct scsi_cd *cd;

	cd = scsi_cd_get(disk);
	if (!cd)
		return -ENXIO;

	/* if the unit is not ready, nothing more to do */
	if (scsi_test_unit_ready(cd->device, SR_TIMEOUT, MAX_RETRIES, &sshdr))
		goto out;

	sr_cd_check(&cd->cdi);
	get_sectorsize(cd);
out:
	scsi_cd_put(cd);
	return 0;
}