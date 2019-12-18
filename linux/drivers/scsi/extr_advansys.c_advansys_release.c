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
struct TYPE_3__ {int /*<<< orphan*/  overrun_buf; int /*<<< orphan*/  overrun_dma; } ;
struct TYPE_4__ {TYPE_1__ asc_dvc_var; } ;
struct asc_board {int /*<<< orphan*/  ioremap_addr; TYPE_2__ dvc_var; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct Scsi_Host {scalar_t__ dma_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_DBG (int,char*) ; 
 scalar_t__ ASC_NARROW_BOARD (struct asc_board*) ; 
 int /*<<< orphan*/  ASC_OVERRUN_BSIZE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ NO_ISA_DMA ; 
 int /*<<< orphan*/  advansys_wide_free_mem (struct asc_board*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct asc_board* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int advansys_release(struct Scsi_Host *shost)
{
	struct asc_board *board = shost_priv(shost);
	ASC_DBG(1, "begin\n");
	scsi_remove_host(shost);
	free_irq(board->irq, shost);
#ifdef CONFIG_ISA
	if (shost->dma_channel != NO_ISA_DMA) {
		ASC_DBG(1, "free_dma()\n");
		free_dma(shost->dma_channel);
	}
#endif
	if (ASC_NARROW_BOARD(board)) {
		dma_unmap_single(board->dev,
					board->dvc_var.asc_dvc_var.overrun_dma,
					ASC_OVERRUN_BSIZE, DMA_FROM_DEVICE);
		kfree(board->dvc_var.asc_dvc_var.overrun_buf);
	} else {
		iounmap(board->ioremap_addr);
		advansys_wide_free_mem(board);
	}
	scsi_host_put(shost);
	ASC_DBG(1, "end\n");
	return 0;
}