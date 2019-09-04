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
typedef  int uint32_t ;
struct jz4780_dma_dev {int dummy; } ;
struct TYPE_7__ {TYPE_2__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_3__ chan; } ;
struct jz4780_dma_chan {TYPE_4__ vchan; TYPE_1__* desc; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int status; scalar_t__ type; int /*<<< orphan*/  vdesc; } ;

/* Variables and functions */
 scalar_t__ DMA_CYCLIC ; 
 int JZ_DMA_DCS_AR ; 
 int JZ_DMA_DCS_HLT ; 
 int /*<<< orphan*/  JZ_DMA_REG_DCS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  jz4780_dma_begin (struct jz4780_dma_chan*) ; 
 int jz4780_dma_readl (struct jz4780_dma_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_dma_writel (struct jz4780_dma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jz4780_dma_chan_irq(struct jz4780_dma_dev *jzdma,
	struct jz4780_dma_chan *jzchan)
{
	uint32_t dcs;

	spin_lock(&jzchan->vchan.lock);

	dcs = jz4780_dma_readl(jzdma, JZ_DMA_REG_DCS(jzchan->id));
	jz4780_dma_writel(jzdma, JZ_DMA_REG_DCS(jzchan->id), 0);

	if (dcs & JZ_DMA_DCS_AR) {
		dev_warn(&jzchan->vchan.chan.dev->device,
			 "address error (DCS=0x%x)\n", dcs);
	}

	if (dcs & JZ_DMA_DCS_HLT) {
		dev_warn(&jzchan->vchan.chan.dev->device,
			 "channel halt (DCS=0x%x)\n", dcs);
	}

	if (jzchan->desc) {
		jzchan->desc->status = dcs;

		if ((dcs & (JZ_DMA_DCS_AR | JZ_DMA_DCS_HLT)) == 0) {
			if (jzchan->desc->type == DMA_CYCLIC) {
				vchan_cyclic_callback(&jzchan->desc->vdesc);
			} else {
				vchan_cookie_complete(&jzchan->desc->vdesc);
				jzchan->desc = NULL;
			}

			jz4780_dma_begin(jzchan);
		}
	} else {
		dev_err(&jzchan->vchan.chan.dev->device,
			"channel IRQ with no active transfer\n");
	}

	spin_unlock(&jzchan->vchan.lock);
}