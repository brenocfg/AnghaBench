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
struct mailbox {int dummy; } ;
struct device {int dummy; } ;
struct ccb {int dummy; } ;
struct aha1542_hostdata {int /*<<< orphan*/  mb_handle; int /*<<< orphan*/  mb; int /*<<< orphan*/  ccb_handle; int /*<<< orphan*/  ccb; } ;
struct Scsi_Host {int dma_channel; scalar_t__ n_io_port; scalar_t__ io_port; scalar_t__ irq; struct device* dma_dev; } ;

/* Variables and functions */
 int AHA1542_MAILBOXES ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (int) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct Scsi_Host*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct aha1542_hostdata* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int aha1542_release(struct Scsi_Host *sh)
{
	struct aha1542_hostdata *aha1542 = shost_priv(sh);
	struct device *dev = sh->dma_dev;

	scsi_remove_host(sh);
	if (sh->dma_channel != 0xff)
		free_dma(sh->dma_channel);
	dma_free_coherent(dev, AHA1542_MAILBOXES * sizeof(struct ccb),
			  aha1542->ccb, aha1542->ccb_handle);
	dma_free_coherent(dev, AHA1542_MAILBOXES * 2 * sizeof(struct mailbox),
			  aha1542->mb, aha1542->mb_handle);
	if (sh->irq)
		free_irq(sh->irq, sh);
	if (sh->io_port && sh->n_io_port)
		release_region(sh->io_port, sh->n_io_port);
	scsi_host_put(sh);
	return 0;
}