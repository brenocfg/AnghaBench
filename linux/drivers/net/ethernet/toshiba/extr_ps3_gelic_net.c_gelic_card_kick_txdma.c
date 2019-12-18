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
struct gelic_descr {int /*<<< orphan*/  bus_addr; } ;
struct gelic_card {int tx_dma_progress; } ;

/* Variables and functions */
 scalar_t__ GELIC_DESCR_DMA_CARDOWNED ; 
 int /*<<< orphan*/  bus_id (struct gelic_card*) ; 
 int /*<<< orphan*/  ctodev (struct gelic_card*) ; 
 int /*<<< orphan*/  dev_id (struct gelic_card*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ gelic_descr_get_status (struct gelic_descr*) ; 
 int lv1_net_start_tx_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gelic_card_kick_txdma(struct gelic_card *card,
				 struct gelic_descr *descr)
{
	int status = 0;

	if (card->tx_dma_progress)
		return 0;

	if (gelic_descr_get_status(descr) == GELIC_DESCR_DMA_CARDOWNED) {
		card->tx_dma_progress = 1;
		status = lv1_net_start_tx_dma(bus_id(card), dev_id(card),
					      descr->bus_addr, 0);
		if (status) {
			card->tx_dma_progress = 0;
			dev_info(ctodev(card), "lv1_net_start_txdma failed," \
				 "status=%d\n", status);
		}
	}
	return status;
}