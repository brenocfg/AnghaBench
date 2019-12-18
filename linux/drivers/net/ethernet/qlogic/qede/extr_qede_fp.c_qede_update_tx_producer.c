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
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct qede_tx_queue {int /*<<< orphan*/  doorbell_addr; TYPE_1__ tx_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qede_update_tx_producer(struct qede_tx_queue *txq)
{
	/* wmb makes sure that the BDs data is updated before updating the
	 * producer, otherwise FW may read old data from the BDs.
	 */
	wmb();
	barrier();
	writel(txq->tx_db.raw, txq->doorbell_addr);

	/* Fence required to flush the write combined buffer, since another
	 * CPU may write to the same doorbell address and data may be lost
	 * due to relaxed order nature of write combined bar.
	 */
	wmb();
}