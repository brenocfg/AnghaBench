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
typedef  int /*<<< orphan*/  u32 ;
struct mvneta_tx_queue {int /*<<< orphan*/  id; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_TXQ_SENT_THRESH_ALL_MASK ; 
 int /*<<< orphan*/  MVNETA_TXQ_SENT_THRESH_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVNETA_TXQ_SIZE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_tx_done_pkts_coal_set(struct mvneta_port *pp,
					 struct mvneta_tx_queue *txq, u32 value)
{
	u32 val;

	val = mvreg_read(pp, MVNETA_TXQ_SIZE_REG(txq->id));

	val &= ~MVNETA_TXQ_SENT_THRESH_ALL_MASK;
	val |= MVNETA_TXQ_SENT_THRESH_MASK(value);

	mvreg_write(pp, MVNETA_TXQ_SIZE_REG(txq->id), val);
}