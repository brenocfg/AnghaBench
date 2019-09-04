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
struct bgmac_dma_ring {scalar_t__ mmio_base; } ;
struct bgmac {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BGMAC_DMA_RX_CTL ; 
 int /*<<< orphan*/  BGMAC_DMA_RX_STAT ; 
 scalar_t__ BGMAC_DMA_RX_STATUS ; 
 int /*<<< orphan*/  BGMAC_DMA_RX_STAT_DISABLED ; 
 int /*<<< orphan*/  bgmac_wait_value (struct bgmac*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bgmac_write (struct bgmac*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void bgmac_dma_rx_reset(struct bgmac *bgmac, struct bgmac_dma_ring *ring)
{
	if (!ring->mmio_base)
		return;

	bgmac_write(bgmac, ring->mmio_base + BGMAC_DMA_RX_CTL, 0);
	if (!bgmac_wait_value(bgmac,
			      ring->mmio_base + BGMAC_DMA_RX_STATUS,
			      BGMAC_DMA_RX_STAT, BGMAC_DMA_RX_STAT_DISABLED,
			      10000))
		dev_err(bgmac->dev, "Reset of ring 0x%X RX failed\n",
			ring->mmio_base);
}