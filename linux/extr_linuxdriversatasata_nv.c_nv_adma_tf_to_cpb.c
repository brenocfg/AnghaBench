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
struct ata_taskfile {int flags; int hob_feature; int hob_nsect; int hob_lbal; int hob_lbam; int hob_lbah; int feature; int nsect; int lbal; int lbam; int lbah; int device; int command; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ATA_REG_CMD ; 
 int ATA_REG_DEVICE ; 
 int ATA_REG_ERR ; 
 int ATA_REG_LBAH ; 
 int ATA_REG_LBAL ; 
 int ATA_REG_LBAM ; 
 int ATA_REG_NSECT ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA48 ; 
 int CMDEND ; 
 int IGN ; 
 int WNB ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static unsigned int nv_adma_tf_to_cpb(struct ata_taskfile *tf, __le16 *cpb)
{
	unsigned int idx = 0;

	if (tf->flags & ATA_TFLAG_ISADDR) {
		if (tf->flags & ATA_TFLAG_LBA48) {
			cpb[idx++] = cpu_to_le16((ATA_REG_ERR   << 8) | tf->hob_feature | WNB);
			cpb[idx++] = cpu_to_le16((ATA_REG_NSECT << 8) | tf->hob_nsect);
			cpb[idx++] = cpu_to_le16((ATA_REG_LBAL  << 8) | tf->hob_lbal);
			cpb[idx++] = cpu_to_le16((ATA_REG_LBAM  << 8) | tf->hob_lbam);
			cpb[idx++] = cpu_to_le16((ATA_REG_LBAH  << 8) | tf->hob_lbah);
			cpb[idx++] = cpu_to_le16((ATA_REG_ERR    << 8) | tf->feature);
		} else
			cpb[idx++] = cpu_to_le16((ATA_REG_ERR    << 8) | tf->feature | WNB);

		cpb[idx++] = cpu_to_le16((ATA_REG_NSECT  << 8) | tf->nsect);
		cpb[idx++] = cpu_to_le16((ATA_REG_LBAL   << 8) | tf->lbal);
		cpb[idx++] = cpu_to_le16((ATA_REG_LBAM   << 8) | tf->lbam);
		cpb[idx++] = cpu_to_le16((ATA_REG_LBAH   << 8) | tf->lbah);
	}

	if (tf->flags & ATA_TFLAG_DEVICE)
		cpb[idx++] = cpu_to_le16((ATA_REG_DEVICE << 8) | tf->device);

	cpb[idx++] = cpu_to_le16((ATA_REG_CMD    << 8) | tf->command | CMDEND);

	while (idx < 12)
		cpb[idx++] = cpu_to_le16(IGN);

	return idx;
}