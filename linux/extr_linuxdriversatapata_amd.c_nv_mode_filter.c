#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ata_port {scalar_t__ port_no; TYPE_2__* host; } ;
struct ata_device {scalar_t__ devno; TYPE_1__* link; } ;
struct ata_acpi_gtm {int flags; TYPE_3__* drive; } ;
typedef  int /*<<< orphan*/  acpi_str ;
struct TYPE_6__ {int dma; } ;
struct TYPE_5__ {scalar_t__ private_data; } ;
struct TYPE_4__ {struct ata_port* ap; } ;

/* Variables and functions */
 unsigned long ATA_MASK_MWDMA ; 
 unsigned long ATA_MASK_PIO ; 
 unsigned long ATA_MASK_UDMA ; 
 int /*<<< orphan*/  ATA_MWDMA2 ; 
 int /*<<< orphan*/  ATA_PIO4 ; 
#define  ATA_UDMA0 134 
#define  ATA_UDMA1 133 
#define  ATA_UDMA2 132 
#define  ATA_UDMA3 131 
#define  ATA_UDMA4 130 
#define  ATA_UDMA5 129 
#define  ATA_UDMA6 128 
 unsigned long ata_acpi_gtm_xfermask (struct ata_device*,struct ata_acpi_gtm const*) ; 
 struct ata_acpi_gtm* ata_acpi_init_gtm (struct ata_port*) ; 
 unsigned long ata_pack_xfermask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  ata_port_dbg (struct ata_port*,char*,unsigned long,unsigned long,unsigned long,unsigned long,int,unsigned long,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 

__attribute__((used)) static unsigned long nv_mode_filter(struct ata_device *dev,
				    unsigned long xfer_mask)
{
	static const unsigned int udma_mask_map[] =
		{ ATA_UDMA2, ATA_UDMA1, ATA_UDMA0, 0,
		  ATA_UDMA3, ATA_UDMA4, ATA_UDMA5, ATA_UDMA6 };
	struct ata_port *ap = dev->link->ap;
	char acpi_str[32] = "";
	u32 saved_udma, udma;
	const struct ata_acpi_gtm *gtm;
	unsigned long bios_limit = 0, acpi_limit = 0, limit;

	/* find out what BIOS configured */
	udma = saved_udma = (unsigned long)ap->host->private_data;

	if (ap->port_no == 0)
		udma >>= 16;
	if (dev->devno == 0)
		udma >>= 8;

	if ((udma & 0xc0) == 0xc0)
		bios_limit = ata_pack_xfermask(0, 0, udma_mask_map[udma & 0x7]);

	/* consult ACPI GTM too */
	gtm = ata_acpi_init_gtm(ap);
	if (gtm) {
		acpi_limit = ata_acpi_gtm_xfermask(dev, gtm);

		snprintf(acpi_str, sizeof(acpi_str), " (%u:%u:0x%x)",
			 gtm->drive[0].dma, gtm->drive[1].dma, gtm->flags);
	}

	/* be optimistic, EH can take care of things if something goes wrong */
	limit = bios_limit | acpi_limit;

	/* If PIO or DMA isn't configured at all, don't limit.  Let EH
	 * handle it.
	 */
	if (!(limit & ATA_MASK_PIO))
		limit |= ATA_MASK_PIO;
	if (!(limit & (ATA_MASK_MWDMA | ATA_MASK_UDMA)))
		limit |= ATA_MASK_MWDMA | ATA_MASK_UDMA;
	/* PIO4, MWDMA2, UDMA2 should always be supported regardless of
	   cable detection result */
	limit |= ata_pack_xfermask(ATA_PIO4, ATA_MWDMA2, ATA_UDMA2);

	ata_port_dbg(ap, "nv_mode_filter: 0x%lx&0x%lx->0x%lx, "
			"BIOS=0x%lx (0x%x) ACPI=0x%lx%s\n",
			xfer_mask, limit, xfer_mask & limit, bios_limit,
			saved_udma, acpi_limit, acpi_str);

	return xfer_mask & limit;
}