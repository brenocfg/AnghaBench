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
typedef  int u32 ;
struct bgmac_dma_ring {scalar_t__ mmio_base; } ;
struct bgmac {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BGMAC_DMA_TX_CTL ; 
 int BGMAC_DMA_TX_STAT ; 
 scalar_t__ BGMAC_DMA_TX_STATUS ; 
 int BGMAC_DMA_TX_STAT_DISABLED ; 
 int BGMAC_DMA_TX_STAT_IDLEWAIT ; 
 int BGMAC_DMA_TX_STAT_STOPPED ; 
 int /*<<< orphan*/  BGMAC_DMA_TX_SUSPEND ; 
 int bgmac_read (struct bgmac*,scalar_t__) ; 
 int /*<<< orphan*/  bgmac_wait_value (struct bgmac*,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  bgmac_write (struct bgmac*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bgmac_dma_tx_reset(struct bgmac *bgmac, struct bgmac_dma_ring *ring)
{
	u32 val;
	int i;

	if (!ring->mmio_base)
		return;

	/* Suspend DMA TX ring first.
	 * bgmac_wait_value doesn't support waiting for any of few values, so
	 * implement whole loop here.
	 */
	bgmac_write(bgmac, ring->mmio_base + BGMAC_DMA_TX_CTL,
		    BGMAC_DMA_TX_SUSPEND);
	for (i = 0; i < 10000 / 10; i++) {
		val = bgmac_read(bgmac, ring->mmio_base + BGMAC_DMA_TX_STATUS);
		val &= BGMAC_DMA_TX_STAT;
		if (val == BGMAC_DMA_TX_STAT_DISABLED ||
		    val == BGMAC_DMA_TX_STAT_IDLEWAIT ||
		    val == BGMAC_DMA_TX_STAT_STOPPED) {
			i = 0;
			break;
		}
		udelay(10);
	}
	if (i)
		dev_err(bgmac->dev, "Timeout suspending DMA TX ring 0x%X (BGMAC_DMA_TX_STAT: 0x%08X)\n",
			ring->mmio_base, val);

	/* Remove SUSPEND bit */
	bgmac_write(bgmac, ring->mmio_base + BGMAC_DMA_TX_CTL, 0);
	if (!bgmac_wait_value(bgmac,
			      ring->mmio_base + BGMAC_DMA_TX_STATUS,
			      BGMAC_DMA_TX_STAT, BGMAC_DMA_TX_STAT_DISABLED,
			      10000)) {
		dev_warn(bgmac->dev, "DMA TX ring 0x%X wasn't disabled on time, waiting additional 300us\n",
			 ring->mmio_base);
		udelay(300);
		val = bgmac_read(bgmac, ring->mmio_base + BGMAC_DMA_TX_STATUS);
		if ((val & BGMAC_DMA_TX_STAT) != BGMAC_DMA_TX_STAT_DISABLED)
			dev_err(bgmac->dev, "Reset of DMA TX ring 0x%X failed\n",
				ring->mmio_base);
	}
}