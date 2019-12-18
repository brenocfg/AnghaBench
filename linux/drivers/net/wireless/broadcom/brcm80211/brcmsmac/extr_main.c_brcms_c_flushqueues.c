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
typedef  size_t uint ;
struct brcms_hardware {scalar_t__* di; } ;
struct brcms_c_info {TYPE_1__* pub; struct brcms_hardware* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ieee_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RANGE_ALL ; 
 size_t NFIFO ; 
 size_t RX_FIFO ; 
 size_t TX_BCMC_FIFO ; 
 int /*<<< orphan*/  brcms_fifo_to_ac (size_t) ; 
 int /*<<< orphan*/  dma_rxreclaim (scalar_t__) ; 
 int /*<<< orphan*/  dma_txreclaim (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_flushqueues(struct brcms_c_info *wlc)
{
	struct brcms_hardware *wlc_hw = wlc->hw;
	uint i;

	/* free any posted tx packets */
	for (i = 0; i < NFIFO; i++) {
		if (wlc_hw->di[i]) {
			dma_txreclaim(wlc_hw->di[i], DMA_RANGE_ALL);
			if (i < TX_BCMC_FIFO)
				ieee80211_wake_queue(wlc->pub->ieee_hw,
						     brcms_fifo_to_ac(i));
		}
	}

	/* free any posted rx packets */
	dma_rxreclaim(wlc_hw->di[RX_FIFO]);
}