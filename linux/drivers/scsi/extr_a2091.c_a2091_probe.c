#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * SCMD; int /*<<< orphan*/ * SASR; } ;
typedef  TYPE_3__ wd33c93_regs ;
struct zorro_device_id {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; } ;
struct zorro_dev {TYPE_2__ resource; int /*<<< orphan*/  slotaddr; } ;
struct a2091_scsiregs {int CNTR; int /*<<< orphan*/  SCMD; int /*<<< orphan*/  SASR; int /*<<< orphan*/  DAWR; } ;
struct TYPE_5__ {int no_sync; int /*<<< orphan*/  dma_mode; scalar_t__ fast; } ;
struct a2091_hostdata {struct a2091_scsiregs* regs; TYPE_1__ wh; } ;
struct Scsi_Host {int /*<<< orphan*/  unique_id; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int CNTR_INTEN ; 
 int CNTR_PDMD ; 
 int /*<<< orphan*/  CTRL_DMA ; 
 int /*<<< orphan*/  DAWR_A2091 ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_AMIGA_PORTS ; 
 int /*<<< orphan*/  WD33C93_FS_8_10 ; 
 struct a2091_scsiregs* ZTWO_VADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2091_intr ; 
 int /*<<< orphan*/  a2091_scsi_template ; 
 int /*<<< orphan*/  dma_setup ; 
 int /*<<< orphan*/  dma_stop ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int,char*) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 struct a2091_hostdata* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  wd33c93_init (struct Scsi_Host*,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zorro_set_drvdata (struct zorro_dev*,struct Scsi_Host*) ; 

__attribute__((used)) static int a2091_probe(struct zorro_dev *z, const struct zorro_device_id *ent)
{
	struct Scsi_Host *instance;
	int error;
	struct a2091_scsiregs *regs;
	wd33c93_regs wdregs;
	struct a2091_hostdata *hdata;

	if (!request_mem_region(z->resource.start, 256, "wd33c93"))
		return -EBUSY;

	instance = scsi_host_alloc(&a2091_scsi_template,
				   sizeof(struct a2091_hostdata));
	if (!instance) {
		error = -ENOMEM;
		goto fail_alloc;
	}

	instance->irq = IRQ_AMIGA_PORTS;
	instance->unique_id = z->slotaddr;

	regs = ZTWO_VADDR(z->resource.start);
	regs->DAWR = DAWR_A2091;

	wdregs.SASR = &regs->SASR;
	wdregs.SCMD = &regs->SCMD;

	hdata = shost_priv(instance);
	hdata->wh.no_sync = 0xff;
	hdata->wh.fast = 0;
	hdata->wh.dma_mode = CTRL_DMA;
	hdata->regs = regs;

	wd33c93_init(instance, wdregs, dma_setup, dma_stop, WD33C93_FS_8_10);
	error = request_irq(IRQ_AMIGA_PORTS, a2091_intr, IRQF_SHARED,
			    "A2091 SCSI", instance);
	if (error)
		goto fail_irq;

	regs->CNTR = CNTR_PDMD | CNTR_INTEN;

	error = scsi_add_host(instance, NULL);
	if (error)
		goto fail_host;

	zorro_set_drvdata(z, instance);

	scsi_scan_host(instance);
	return 0;

fail_host:
	free_irq(IRQ_AMIGA_PORTS, instance);
fail_irq:
	scsi_host_put(instance);
fail_alloc:
	release_mem_region(z->resource.start, 256);
	return error;
}