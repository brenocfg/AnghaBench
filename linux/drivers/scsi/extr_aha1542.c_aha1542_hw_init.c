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
struct scsi_host_template {int dummy; } ;
struct mailbox {int dummy; } ;
struct device {int dummy; } ;
struct ccb {int dummy; } ;
struct aha1542_hostdata {int aha1542_last_mbi_used; int aha1542_last_mbo_used; scalar_t__ bios_translation; int /*<<< orphan*/  mb_handle; void* mb; int /*<<< orphan*/  ccb_handle; void* ccb; } ;
struct Scsi_Host {unsigned int unique_id; unsigned int io_port; int dma_channel; int /*<<< orphan*/  irq; int /*<<< orphan*/  this_id; int /*<<< orphan*/  n_io_port; } ;
typedef  int /*<<< orphan*/  dma_info ;

/* Variables and functions */
 int AHA1542_MAILBOXES ; 
 int /*<<< orphan*/  AHA1542_REGION_SIZE ; 
 scalar_t__ BIOS_TRANSLATION_25563 ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_MODE_CASCADE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int aha1542_getconfig (struct Scsi_Host*) ; 
 int /*<<< orphan*/  aha1542_interrupt ; 
 scalar_t__ aha1542_query (struct Scsi_Host*) ; 
 int /*<<< orphan*/  aha1542_set_bus_times (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aha1542_test_port (struct Scsi_Host*) ; 
 int /*<<< orphan*/ * bus_off ; 
 int /*<<< orphan*/ * bus_on ; 
 void* dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_speed ; 
 int /*<<< orphan*/  enable_dma (int) ; 
 int /*<<< orphan*/  free_dma (int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 unsigned int* io ; 
 int /*<<< orphan*/  release_region (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ request_dma (int,char*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  request_region (unsigned int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ scsi_add_host (struct Scsi_Host*,struct device*) ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  set_dma_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_mailboxes (struct Scsi_Host*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,...) ; 
 struct aha1542_hostdata* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static struct Scsi_Host *aha1542_hw_init(struct scsi_host_template *tpnt, struct device *pdev, int indx)
{
	unsigned int base_io = io[indx];
	struct Scsi_Host *sh;
	struct aha1542_hostdata *aha1542;
	char dma_info[] = "no DMA";

	if (base_io == 0)
		return NULL;

	if (!request_region(base_io, AHA1542_REGION_SIZE, "aha1542"))
		return NULL;

	sh = scsi_host_alloc(tpnt, sizeof(struct aha1542_hostdata));
	if (!sh)
		goto release;
	aha1542 = shost_priv(sh);

	sh->unique_id = base_io;
	sh->io_port = base_io;
	sh->n_io_port = AHA1542_REGION_SIZE;
	aha1542->aha1542_last_mbi_used = 2 * AHA1542_MAILBOXES - 1;
	aha1542->aha1542_last_mbo_used = AHA1542_MAILBOXES - 1;

	if (!aha1542_test_port(sh))
		goto unregister;

	aha1542_set_bus_times(sh, bus_on[indx], bus_off[indx], dma_speed[indx]);
	if (aha1542_query(sh))
		goto unregister;
	if (aha1542_getconfig(sh) == -1)
		goto unregister;

	if (sh->dma_channel != 0xFF)
		snprintf(dma_info, sizeof(dma_info), "DMA %d", sh->dma_channel);
	shost_printk(KERN_INFO, sh, "Adaptec AHA-1542 (SCSI-ID %d) at IO 0x%x, IRQ %d, %s\n",
				sh->this_id, base_io, sh->irq, dma_info);
	if (aha1542->bios_translation == BIOS_TRANSLATION_25563)
		shost_printk(KERN_INFO, sh, "Using extended bios translation\n");

	if (dma_set_mask_and_coherent(pdev, DMA_BIT_MASK(24)) < 0)
		goto unregister;

	aha1542->mb = dma_alloc_coherent(pdev,
			AHA1542_MAILBOXES * 2 * sizeof(struct mailbox),
			&aha1542->mb_handle, GFP_KERNEL);
	if (!aha1542->mb)
		goto unregister;

	aha1542->ccb = dma_alloc_coherent(pdev,
			AHA1542_MAILBOXES * sizeof(struct ccb),
			&aha1542->ccb_handle, GFP_KERNEL);
	if (!aha1542->ccb)
		goto free_mb;

	setup_mailboxes(sh);

	if (request_irq(sh->irq, aha1542_interrupt, 0, "aha1542", sh)) {
		shost_printk(KERN_ERR, sh, "Unable to allocate IRQ.\n");
		goto free_ccb;
	}
	if (sh->dma_channel != 0xFF) {
		if (request_dma(sh->dma_channel, "aha1542")) {
			shost_printk(KERN_ERR, sh, "Unable to allocate DMA channel.\n");
			goto free_irq;
		}
		if (sh->dma_channel == 0 || sh->dma_channel >= 5) {
			set_dma_mode(sh->dma_channel, DMA_MODE_CASCADE);
			enable_dma(sh->dma_channel);
		}
	}

	if (scsi_add_host(sh, pdev))
		goto free_dma;

	scsi_scan_host(sh);

	return sh;

free_dma:
	if (sh->dma_channel != 0xff)
		free_dma(sh->dma_channel);
free_irq:
	free_irq(sh->irq, sh);
free_ccb:
	dma_free_coherent(pdev, AHA1542_MAILBOXES * sizeof(struct ccb),
			  aha1542->ccb, aha1542->ccb_handle);
free_mb:
	dma_free_coherent(pdev, AHA1542_MAILBOXES * 2 * sizeof(struct mailbox),
			  aha1542->mb, aha1542->mb_handle);
unregister:
	scsi_host_put(sh);
release:
	release_region(base_io, AHA1542_REGION_SIZE);

	return NULL;
}