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
struct gelic_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_id (struct gelic_card*) ; 
 int /*<<< orphan*/  ctodev (struct gelic_card*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_id (struct gelic_card*) ; 
 int lv1_net_stop_tx_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gelic_card_disable_txdmac(struct gelic_card *card)
{
	int status;

	/* this hvc blocks until the DMA in progress really stopped */
	status = lv1_net_stop_tx_dma(bus_id(card), dev_id(card));
	if (status)
		dev_err(ctodev(card),
			"lv1_net_stop_tx_dma failed, status=%d\n", status);
}