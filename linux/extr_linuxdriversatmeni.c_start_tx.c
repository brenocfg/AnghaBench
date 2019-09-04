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
struct eni_dev {TYPE_1__* tx; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/ * ubr; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  tx_mult; int /*<<< orphan*/  tx_bw; scalar_t__ lost; } ;
struct atm_dev {int dummy; } ;
struct TYPE_2__ {int index; int /*<<< orphan*/ * send; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_OC3_PCR ; 
 int /*<<< orphan*/  DEFAULT_TX_MULT ; 
 struct eni_dev* ENI_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  MID_DMA_WR_TX ; 
 int NR_CHAN ; 
 int /*<<< orphan*/  eni_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_tx(struct atm_dev *dev)
{
	struct eni_dev *eni_dev;
	int i;

	eni_dev = ENI_DEV(dev);
	eni_dev->lost = 0;
	eni_dev->tx_bw = ATM_OC3_PCR;
	eni_dev->tx_mult = DEFAULT_TX_MULT;
	init_waitqueue_head(&eni_dev->tx_wait);
	eni_dev->ubr = NULL;
	skb_queue_head_init(&eni_dev->tx_queue);
	eni_out(0,MID_DMA_WR_TX);
	for (i = 0; i < NR_CHAN; i++) {
		eni_dev->tx[i].send = NULL;
		eni_dev->tx[i].index = i;
	}
	return 0;
}