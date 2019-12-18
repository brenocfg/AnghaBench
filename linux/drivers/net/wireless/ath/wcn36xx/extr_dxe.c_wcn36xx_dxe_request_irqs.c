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
struct wcn36xx {int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wcn36xx*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_err (char*) ; 
 int /*<<< orphan*/  wcn36xx_irq_rx_ready ; 
 int /*<<< orphan*/  wcn36xx_irq_tx_complete ; 

__attribute__((used)) static int wcn36xx_dxe_request_irqs(struct wcn36xx *wcn)
{
	int ret;

	ret = request_irq(wcn->tx_irq, wcn36xx_irq_tx_complete,
			  IRQF_TRIGGER_HIGH, "wcn36xx_tx", wcn);
	if (ret) {
		wcn36xx_err("failed to alloc tx irq\n");
		goto out_err;
	}

	ret = request_irq(wcn->rx_irq, wcn36xx_irq_rx_ready, IRQF_TRIGGER_HIGH,
			  "wcn36xx_rx", wcn);
	if (ret) {
		wcn36xx_err("failed to alloc rx irq\n");
		goto out_txirq;
	}

	enable_irq_wake(wcn->rx_irq);

	return 0;

out_txirq:
	free_irq(wcn->tx_irq, wcn);
out_err:
	return ret;

}