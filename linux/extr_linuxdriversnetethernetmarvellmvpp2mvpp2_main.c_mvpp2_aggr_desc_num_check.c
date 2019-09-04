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
struct mvpp2_tx_queue {int count; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MVPP2_AGGR_TXQ_PENDING_MASK ; 
 int MVPP2_AGGR_TXQ_SIZE ; 
 int /*<<< orphan*/  MVPP2_AGGR_TXQ_STATUS_REG (int) ; 
 int mvpp2_read_relaxed (struct mvpp2*,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

__attribute__((used)) static int mvpp2_aggr_desc_num_check(struct mvpp2 *priv,
				     struct mvpp2_tx_queue *aggr_txq, int num)
{
	if ((aggr_txq->count + num) > MVPP2_AGGR_TXQ_SIZE) {
		/* Update number of occupied aggregated Tx descriptors */
		int cpu = smp_processor_id();
		u32 val = mvpp2_read_relaxed(priv,
					     MVPP2_AGGR_TXQ_STATUS_REG(cpu));

		aggr_txq->count = val & MVPP2_AGGR_TXQ_PENDING_MASK;

		if ((aggr_txq->count + num) > MVPP2_AGGR_TXQ_SIZE)
			return -ENOMEM;
	}
	return 0;
}