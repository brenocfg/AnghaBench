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
struct mtk_eth {int /*<<< orphan*/  tx_napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MTK_TX_DONE_INT ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_tx_irq_disable (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mtk_handle_irq_tx(int irq, void *_eth)
{
	struct mtk_eth *eth = _eth;

	if (likely(napi_schedule_prep(&eth->tx_napi))) {
		__napi_schedule(&eth->tx_napi);
		mtk_tx_irq_disable(eth, MTK_TX_DONE_INT);
	}

	return IRQ_HANDLED;
}