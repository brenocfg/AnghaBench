#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {size_t consumed; int /*<<< orphan*/ * addr; int /*<<< orphan*/  length; } ;
struct alcor_sdmmc_host {TYPE_2__ sg_miter; int /*<<< orphan*/  blocks; int /*<<< orphan*/  dev; TYPE_1__* data; scalar_t__ dma_on; struct alcor_pci_priv* alcor_pci; } ;
struct alcor_pci_priv {scalar_t__ iobase; } ;
struct TYPE_4__ {int flags; size_t blksz; } ;

/* Variables and functions */
 scalar_t__ AU6601_REG_BUFFER ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ioread32_rep (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 size_t min (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sg_miter_next (TYPE_2__*) ; 
 int /*<<< orphan*/  sg_miter_stop (TYPE_2__*) ; 

__attribute__((used)) static void alcor_trf_block_pio(struct alcor_sdmmc_host *host, bool read)
{
	struct alcor_pci_priv *priv = host->alcor_pci;
	size_t blksize, len;
	u8 *buf;

	if (!host->blocks)
		return;

	if (host->dma_on) {
		dev_err(host->dev, "configured DMA but got PIO request.\n");
		return;
	}

	if (!!(host->data->flags & MMC_DATA_READ) != read) {
		dev_err(host->dev, "got unexpected direction %i != %i\n",
			!!(host->data->flags & MMC_DATA_READ), read);
	}

	if (!sg_miter_next(&host->sg_miter))
		return;

	blksize = host->data->blksz;
	len = min(host->sg_miter.length, blksize);

	dev_dbg(host->dev, "PIO, %s block size: 0x%zx\n",
		read ? "read" : "write", blksize);

	host->sg_miter.consumed = len;
	host->blocks--;

	buf = host->sg_miter.addr;

	if (read)
		ioread32_rep(priv->iobase + AU6601_REG_BUFFER, buf, len >> 2);
	else
		iowrite32_rep(priv->iobase + AU6601_REG_BUFFER, buf, len >> 2);

	sg_miter_stop(&host->sg_miter);
}