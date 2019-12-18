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
typedef  int u32 ;
struct tusb_omap_dma_ch {int epnum; int /*<<< orphan*/  tbase; scalar_t__ tx; TYPE_1__* musb; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  TUSB_DMA_EP_MAP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int musb_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int tusb_omap_use_shared_dmareq(struct tusb_omap_dma_ch *chdat)
{
	u32		reg = musb_readl(chdat->tbase, TUSB_DMA_EP_MAP);

	if (reg != 0) {
		dev_dbg(chdat->musb->controller, "ep%i dmareq0 is busy for ep%i\n",
			chdat->epnum, reg & 0xf);
		return -EAGAIN;
	}

	if (chdat->tx)
		reg = (1 << 4) | chdat->epnum;
	else
		reg = chdat->epnum;

	musb_writel(chdat->tbase, TUSB_DMA_EP_MAP, reg);

	return 0;
}