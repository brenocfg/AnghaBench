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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct pdc_state {int rx_status_len; scalar_t__ pdc_resp_hdr_len; struct pdc_state* pdc_reg_vbase; struct pdc_regs* regs; void* nrxpost; void* ntxpost; void* nrxd; void* ntxd; struct dma64_regs* rxregs_64; struct dma64_regs* txregs_64; struct pdc_state* pdc_idx; struct platform_device* pdev; } ;
struct pdc_regs {struct dma64* dmaregs; struct pdc_state intmask; } ;
struct dma64_regs {int dummy; } ;
struct TYPE_4__ {struct pdc_state ptr; struct pdc_state control; } ;
struct TYPE_3__ {struct pdc_state ptr; struct pdc_state control; } ;
struct dma64 {TYPE_2__ dmarcv; TYPE_1__ dmaxmt; } ;

/* Variables and functions */
 scalar_t__ PDC_CKSUM_CTRL ; 
 int PDC_CKSUM_CTRL_OFFSET ; 
 int PDC_RINGSET ; 
 void* PDC_RING_ENTRIES ; 
 int PDC_RXREGS_OFFSET ; 
 scalar_t__ PDC_RX_CTL ; 
 scalar_t__ PDC_SPU2_RESP_HDR_LEN ; 
 int PDC_TXREGS_OFFSET ; 
 scalar_t__ PDC_TX_CTL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct pdc_state*) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,struct pdc_state*) ; 

__attribute__((used)) static
void pdc_hw_init(struct pdc_state *pdcs)
{
	struct platform_device *pdev;
	struct device *dev;
	struct dma64 *dma_reg;
	int ringset = PDC_RINGSET;

	pdev = pdcs->pdev;
	dev = &pdev->dev;

	dev_dbg(dev, "PDC %u initial values:", pdcs->pdc_idx);
	dev_dbg(dev, "state structure:                   %p",
		pdcs);
	dev_dbg(dev, " - base virtual addr of hw regs    %p",
		pdcs->pdc_reg_vbase);

	/* initialize data structures */
	pdcs->regs = (struct pdc_regs *)pdcs->pdc_reg_vbase;
	pdcs->txregs_64 = (struct dma64_regs *)
	    (((u8 *)pdcs->pdc_reg_vbase) +
		     PDC_TXREGS_OFFSET + (sizeof(struct dma64) * ringset));
	pdcs->rxregs_64 = (struct dma64_regs *)
	    (((u8 *)pdcs->pdc_reg_vbase) +
		     PDC_RXREGS_OFFSET + (sizeof(struct dma64) * ringset));

	pdcs->ntxd = PDC_RING_ENTRIES;
	pdcs->nrxd = PDC_RING_ENTRIES;
	pdcs->ntxpost = PDC_RING_ENTRIES - 1;
	pdcs->nrxpost = PDC_RING_ENTRIES - 1;
	iowrite32(0, &pdcs->regs->intmask);

	dma_reg = &pdcs->regs->dmaregs[ringset];

	/* Configure DMA but will enable later in pdc_ring_init() */
	iowrite32(PDC_TX_CTL, &dma_reg->dmaxmt.control);

	iowrite32(PDC_RX_CTL + (pdcs->rx_status_len << 1),
		  &dma_reg->dmarcv.control);

	/* Reset current index pointers after making sure DMA is disabled */
	iowrite32(0, &dma_reg->dmaxmt.ptr);
	iowrite32(0, &dma_reg->dmarcv.ptr);

	if (pdcs->pdc_resp_hdr_len == PDC_SPU2_RESP_HDR_LEN)
		iowrite32(PDC_CKSUM_CTRL,
			  pdcs->pdc_reg_vbase + PDC_CKSUM_CTRL_OFFSET);
}