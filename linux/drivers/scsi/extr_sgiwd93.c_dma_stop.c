#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  this_residual; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {TYPE_3__ SCp; TYPE_2__* device; } ;
struct TYPE_8__ {scalar_t__ dma_dir; } ;
struct ip22_hostdata {TYPE_4__ wh; int /*<<< orphan*/  dev; } ;
struct hpc3_scsiregs {int ctrl; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DIR (scalar_t__) ; 
 int HPC3_SCTRL_ACTIVE ; 
 int HPC3_SCTRL_FLUSH ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip22_hostdata* host_to_hostdata (struct Scsi_Host*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void dma_stop(struct Scsi_Host *instance, struct scsi_cmnd *SCpnt,
		     int status)
{
	struct ip22_hostdata *hdata = host_to_hostdata(instance);
	struct hpc3_scsiregs *hregs;

	if (!SCpnt)
		return;

	if (SCpnt->SCp.ptr == NULL || SCpnt->SCp.this_residual == 0)
		return;

	hregs = (struct hpc3_scsiregs *) SCpnt->device->host->base;

	pr_debug("dma_stop: status<%d> ", status);

	/* First stop the HPC and flush it's FIFO. */
	if (hdata->wh.dma_dir) {
		hregs->ctrl |= HPC3_SCTRL_FLUSH;
		while (hregs->ctrl & HPC3_SCTRL_ACTIVE)
			barrier();
	}
	hregs->ctrl = 0;
	dma_unmap_single(hdata->dev, SCpnt->SCp.dma_handle,
			 SCpnt->SCp.this_residual,
			 DMA_DIR(hdata->wh.dma_dir));

	pr_debug("\n");
}