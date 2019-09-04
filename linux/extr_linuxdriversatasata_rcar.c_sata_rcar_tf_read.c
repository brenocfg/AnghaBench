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
struct ata_taskfile {int flags; int ctl; void* hob_lbah; void* hob_lbam; void* hob_lbal; void* hob_nsect; void* hob_feature; void* device; void* lbah; void* lbam; void* lbal; void* nsect; void* feature; int /*<<< orphan*/  command; } ;
struct ata_ioports {int /*<<< orphan*/  ctl_addr; int /*<<< orphan*/  lbah_addr; int /*<<< orphan*/  lbam_addr; int /*<<< orphan*/  lbal_addr; int /*<<< orphan*/  nsect_addr; int /*<<< orphan*/  error_addr; int /*<<< orphan*/  device_addr; } ;
struct ata_port {int last_ctl; struct ata_ioports ioaddr; } ;

/* Variables and functions */
 int ATA_HOB ; 
 int ATA_TFLAG_LBA48 ; 
 void* ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_rcar_check_status (struct ata_port*) ; 

__attribute__((used)) static void sata_rcar_tf_read(struct ata_port *ap, struct ata_taskfile *tf)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;

	tf->command = sata_rcar_check_status(ap);
	tf->feature = ioread32(ioaddr->error_addr);
	tf->nsect = ioread32(ioaddr->nsect_addr);
	tf->lbal = ioread32(ioaddr->lbal_addr);
	tf->lbam = ioread32(ioaddr->lbam_addr);
	tf->lbah = ioread32(ioaddr->lbah_addr);
	tf->device = ioread32(ioaddr->device_addr);

	if (tf->flags & ATA_TFLAG_LBA48) {
		iowrite32(tf->ctl | ATA_HOB, ioaddr->ctl_addr);
		tf->hob_feature = ioread32(ioaddr->error_addr);
		tf->hob_nsect = ioread32(ioaddr->nsect_addr);
		tf->hob_lbal = ioread32(ioaddr->lbal_addr);
		tf->hob_lbam = ioread32(ioaddr->lbam_addr);
		tf->hob_lbah = ioread32(ioaddr->lbah_addr);
		iowrite32(tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
	}
}