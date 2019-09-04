#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct scsi_device {size_t id; int /*<<< orphan*/  request_queue; scalar_t__ lun; scalar_t__ channel; int /*<<< orphan*/  host; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct nv_adma_port_priv {int flags; int /*<<< orphan*/  adma_dma_mask; } ;
struct TYPE_7__ {TYPE_1__* device; } ;
struct ata_port {int port_no; int /*<<< orphan*/  lock; TYPE_4__* host; TYPE_2__ link; struct nv_adma_port_priv* private_data; } ;
struct TYPE_10__ {scalar_t__* dma_mask; } ;
struct TYPE_9__ {TYPE_5__* dev; TYPE_3__** ports; } ;
struct TYPE_8__ {struct nv_adma_port_priv* private_data; } ;
struct TYPE_6__ {scalar_t__ class; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATAPI ; 
 unsigned long ATA_DMA_BOUNDARY ; 
 int /*<<< orphan*/  ATA_DMA_MASK ; 
 size_t ATA_MAX_DEVICES ; 
 int LIBATA_MAX_PRD ; 
 int NV_ADMA_ATAPI_SETUP_COMPLETE ; 
 unsigned long NV_ADMA_DMA_BOUNDARY ; 
 unsigned short NV_ADMA_SGTBL_TOTAL_LEN ; 
 int /*<<< orphan*/  NV_MCP_SATA_CFG_20 ; 
 int NV_MCP_SATA_CFG_20_PORT0_EN ; 
 int NV_MCP_SATA_CFG_20_PORT0_PWB_EN ; 
 int NV_MCP_SATA_CFG_20_PORT1_EN ; 
 int NV_MCP_SATA_CFG_20_PORT1_PWB_EN ; 
 int /*<<< orphan*/  ata_port_info (struct ata_port*,char*,unsigned long long,unsigned long,unsigned short) ; 
 int ata_scsi_slave_config (struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segments (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  blk_queue_segment_boundary (int /*<<< orphan*/ ,unsigned long) ; 
 int dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_adma_register_mode (struct ata_port*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct pci_dev* to_pci_dev (TYPE_5__*) ; 

__attribute__((used)) static int nv_adma_slave_config(struct scsi_device *sdev)
{
	struct ata_port *ap = ata_shost_to_port(sdev->host);
	struct nv_adma_port_priv *pp = ap->private_data;
	struct nv_adma_port_priv *port0, *port1;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned long segment_boundary, flags;
	unsigned short sg_tablesize;
	int rc;
	int adma_enable;
	u32 current_reg, new_reg, config_mask;

	rc = ata_scsi_slave_config(sdev);

	if (sdev->id >= ATA_MAX_DEVICES || sdev->channel || sdev->lun)
		/* Not a proper libata device, ignore */
		return rc;

	spin_lock_irqsave(ap->lock, flags);

	if (ap->link.device[sdev->id].class == ATA_DEV_ATAPI) {
		/*
		 * NVIDIA reports that ADMA mode does not support ATAPI commands.
		 * Therefore ATAPI commands are sent through the legacy interface.
		 * However, the legacy interface only supports 32-bit DMA.
		 * Restrict DMA parameters as required by the legacy interface
		 * when an ATAPI device is connected.
		 */
		segment_boundary = ATA_DMA_BOUNDARY;
		/* Subtract 1 since an extra entry may be needed for padding, see
		   libata-scsi.c */
		sg_tablesize = LIBATA_MAX_PRD - 1;

		/* Since the legacy DMA engine is in use, we need to disable ADMA
		   on the port. */
		adma_enable = 0;
		nv_adma_register_mode(ap);
	} else {
		segment_boundary = NV_ADMA_DMA_BOUNDARY;
		sg_tablesize = NV_ADMA_SGTBL_TOTAL_LEN;
		adma_enable = 1;
	}

	pci_read_config_dword(pdev, NV_MCP_SATA_CFG_20, &current_reg);

	if (ap->port_no == 1)
		config_mask = NV_MCP_SATA_CFG_20_PORT1_EN |
			      NV_MCP_SATA_CFG_20_PORT1_PWB_EN;
	else
		config_mask = NV_MCP_SATA_CFG_20_PORT0_EN |
			      NV_MCP_SATA_CFG_20_PORT0_PWB_EN;

	if (adma_enable) {
		new_reg = current_reg | config_mask;
		pp->flags &= ~NV_ADMA_ATAPI_SETUP_COMPLETE;
	} else {
		new_reg = current_reg & ~config_mask;
		pp->flags |= NV_ADMA_ATAPI_SETUP_COMPLETE;
	}

	if (current_reg != new_reg)
		pci_write_config_dword(pdev, NV_MCP_SATA_CFG_20, new_reg);

	port0 = ap->host->ports[0]->private_data;
	port1 = ap->host->ports[1]->private_data;
	if ((port0->flags & NV_ADMA_ATAPI_SETUP_COMPLETE) ||
	    (port1->flags & NV_ADMA_ATAPI_SETUP_COMPLETE)) {
		/*
		 * We have to set the DMA mask to 32-bit if either port is in
		 * ATAPI mode, since they are on the same PCI device which is
		 * used for DMA mapping.  If either SCSI device is not allocated
		 * yet, it's OK since that port will discover its correct
		 * setting when it does get allocated.
		 */
		rc = dma_set_mask(&pdev->dev, ATA_DMA_MASK);
	} else {
		rc = dma_set_mask(&pdev->dev, pp->adma_dma_mask);
	}

	blk_queue_segment_boundary(sdev->request_queue, segment_boundary);
	blk_queue_max_segments(sdev->request_queue, sg_tablesize);
	ata_port_info(ap,
		      "DMA mask 0x%llX, segment boundary 0x%lX, hw segs %hu\n",
		      (unsigned long long)*ap->host->dev->dma_mask,
		      segment_boundary, sg_tablesize);

	spin_unlock_irqrestore(ap->lock, flags);

	return rc;
}