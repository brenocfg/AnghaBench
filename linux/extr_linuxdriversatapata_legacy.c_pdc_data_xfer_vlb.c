#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ata_queued_cmd {struct ata_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_addr; int /*<<< orphan*/  nsect_addr; } ;
struct ata_port {int pflags; TYPE_2__ ioaddr; } ;
struct ata_device {int /*<<< orphan*/  id; TYPE_1__* link; } ;
typedef  unsigned char __le32 ;
struct TYPE_3__ {struct ata_port* ap; } ;

/* Variables and functions */
 int ATA_PFLAG_PIO32 ; 
 int READ ; 
 scalar_t__ ata_id_has_dword_io (int /*<<< orphan*/ ) ; 
 unsigned int ata_sff_data_xfer32 (struct ata_queued_cmd*,unsigned char*,unsigned int,int) ; 
 unsigned char cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32_rep (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32_rep (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  le32_to_cpu (unsigned char) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int pdc_data_xfer_vlb(struct ata_queued_cmd *qc,
			unsigned char *buf, unsigned int buflen, int rw)
{
	struct ata_device *dev = qc->dev;
	struct ata_port *ap = dev->link->ap;
	int slop = buflen & 3;

	/* 32bit I/O capable *and* we need to write a whole number of dwords */
	if (ata_id_has_dword_io(dev->id) && (slop == 0 || slop == 3)
					&& (ap->pflags & ATA_PFLAG_PIO32)) {
		unsigned long flags;

		local_irq_save(flags);

		/* Perform the 32bit I/O synchronization sequence */
		ioread8(ap->ioaddr.nsect_addr);
		ioread8(ap->ioaddr.nsect_addr);
		ioread8(ap->ioaddr.nsect_addr);

		/* Now the data */
		if (rw == READ)
			ioread32_rep(ap->ioaddr.data_addr, buf, buflen >> 2);
		else
			iowrite32_rep(ap->ioaddr.data_addr, buf, buflen >> 2);

		if (unlikely(slop)) {
			__le32 pad;
			if (rw == READ) {
				pad = cpu_to_le32(ioread32(ap->ioaddr.data_addr));
				memcpy(buf + buflen - slop, &pad, slop);
			} else {
				memcpy(&pad, buf + buflen - slop, slop);
				iowrite32(le32_to_cpu(pad), ap->ioaddr.data_addr);
			}
			buflen += 4 - slop;
		}
		local_irq_restore(flags);
	} else
		buflen = ata_sff_data_xfer32(qc, buf, buflen, rw);

	return buflen;
}