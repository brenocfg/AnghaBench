#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tw68_dev {int /*<<< orphan*/  pci_irqmask; int /*<<< orphan*/  board_virqmask; TYPE_1__* fmt; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct tw68_buf {int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int twformat; } ;

/* Variables and functions */
 int ColorFormatGamma ; 
 int /*<<< orphan*/  TW68_DMAC ; 
 int TW68_DMAP_EN ; 
 int /*<<< orphan*/  TW68_DMAP_SA ; 
 int TW68_FIFO_EN ; 
 int /*<<< orphan*/  TW68_INTMASK ; 
 int /*<<< orphan*/  TW68_INTSTAT ; 
 int /*<<< orphan*/  tw68_set_scale (struct tw68_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_andorl (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tw_clearl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw_setl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tw68_video_start_dma(struct tw68_dev *dev, struct tw68_buf *buf)
{
	/* Set cropping and scaling */
	tw68_set_scale(dev, dev->width, dev->height, dev->field);
	/*
	 *  Set start address for RISC program.  Note that if the DMAP
	 *  processor is currently running, it must be stopped before
	 *  a new address can be set.
	 */
	tw_clearl(TW68_DMAC, TW68_DMAP_EN);
	tw_writel(TW68_DMAP_SA, buf->dma);
	/* Clear any pending interrupts */
	tw_writel(TW68_INTSTAT, dev->board_virqmask);
	/* Enable the risc engine and the fifo */
	tw_andorl(TW68_DMAC, 0xff, dev->fmt->twformat |
		ColorFormatGamma | TW68_DMAP_EN | TW68_FIFO_EN);
	dev->pci_irqmask |= dev->board_virqmask;
	tw_setl(TW68_INTMASK, dev->pci_irqmask);
	return 0;
}