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
struct mvneta_tx_queue {scalar_t__ txq_get_index; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static void mvneta_txq_inc_get(struct mvneta_tx_queue *txq)
{
	txq->txq_get_index++;
	if (txq->txq_get_index == txq->size)
		txq->txq_get_index = 0;
}