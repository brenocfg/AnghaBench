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
struct hinic_txq {struct hinic_sq* sq; } ;
struct hinic_sq {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hinic_txq*) ; 
 int /*<<< orphan*/  tx_napi_del (struct hinic_txq*) ; 

__attribute__((used)) static void tx_free_irq(struct hinic_txq *txq)
{
	struct hinic_sq *sq = txq->sq;

	free_irq(sq->irq, txq);
	tx_napi_del(txq);
}