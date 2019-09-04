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
typedef  scalar_t__ u32 ;
struct mvneta_tx_queue {scalar_t__ pending; int /*<<< orphan*/  id; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_TXQ_UPDATE_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,int) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvneta_txq_pend_desc_add(struct mvneta_port *pp,
				     struct mvneta_tx_queue *txq,
				     int pend_desc)
{
	u32 val;

	pend_desc += txq->pending;

	/* Only 255 Tx descriptors can be added at once */
	do {
		val = min(pend_desc, 255);
		mvreg_write(pp, MVNETA_TXQ_UPDATE_REG(txq->id), val);
		pend_desc -= val;
	} while (pend_desc > 0);
	txq->pending = 0;
}