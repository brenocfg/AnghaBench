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
typedef  int u32 ;
struct mvpp2_tx_queue {int id; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int MVPP2_TXQ_RSVD_REQ_Q_OFFSET ; 
 int /*<<< orphan*/  MVPP2_TXQ_RSVD_REQ_REG ; 
 int MVPP2_TXQ_RSVD_RSLT_MASK ; 
 int /*<<< orphan*/  MVPP2_TXQ_RSVD_RSLT_REG ; 
 int mvpp2_percpu_read_relaxed (struct mvpp2*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_percpu_write_relaxed (struct mvpp2*,int,int /*<<< orphan*/ ,int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static int mvpp2_txq_alloc_reserved_desc(struct mvpp2 *priv,
					 struct mvpp2_tx_queue *txq, int num)
{
	u32 val;
	int cpu = smp_processor_id();

	val = (txq->id << MVPP2_TXQ_RSVD_REQ_Q_OFFSET) | num;
	mvpp2_percpu_write_relaxed(priv, cpu, MVPP2_TXQ_RSVD_REQ_REG, val);

	val = mvpp2_percpu_read_relaxed(priv, cpu, MVPP2_TXQ_RSVD_RSLT_REG);

	return val & MVPP2_TXQ_RSVD_RSLT_MASK;
}