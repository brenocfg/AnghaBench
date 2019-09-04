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
struct scsi_device {int channel; int id; scalar_t__ lun; } ;
struct ata_port {int dummy; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 struct ata_device* ata_find_dev (struct ata_port*,int) ; 
 int /*<<< orphan*/  sata_pmp_attached (struct ata_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ata_device *__ata_scsi_find_dev(struct ata_port *ap,
					      const struct scsi_device *scsidev)
{
	int devno;

	/* skip commands not addressed to targets we simulate */
	if (!sata_pmp_attached(ap)) {
		if (unlikely(scsidev->channel || scsidev->lun))
			return NULL;
		devno = scsidev->id;
	} else {
		if (unlikely(scsidev->id || scsidev->lun))
			return NULL;
		devno = scsidev->channel;
	}

	return ata_find_dev(ap, devno);
}