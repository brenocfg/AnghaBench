#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  q_tx_num; } ;
struct TYPE_5__ {TYPE_1__ cap_queues; } ;
struct ath5k_hw {scalar_t__ ah_version; TYPE_3__* ah_txq; TYPE_2__ ah_capabilities; } ;
struct TYPE_6__ {scalar_t__ tqi_type; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_ASSERT_ENTRY (unsigned int,int /*<<< orphan*/ ) ; 
 int AR5K_QCU_STS_FRMPENDCNT ; 
 int /*<<< orphan*/  AR5K_QCU_TXE ; 
 int /*<<< orphan*/  AR5K_QUEUE_STATUS (unsigned int) ; 
 scalar_t__ AR5K_REG_READ_Q (struct ath5k_hw*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ AR5K_TX_QUEUE_INACTIVE ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

u32
ath5k_hw_num_tx_pending(struct ath5k_hw *ah, unsigned int queue)
{
	u32 pending;
	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/* Return if queue is declared inactive */
	if (ah->ah_txq[queue].tqi_type == AR5K_TX_QUEUE_INACTIVE)
		return false;

	/* XXX: How about AR5K_CFG_TXCNT ? */
	if (ah->ah_version == AR5K_AR5210)
		return false;

	pending = ath5k_hw_reg_read(ah, AR5K_QUEUE_STATUS(queue));
	pending &= AR5K_QCU_STS_FRMPENDCNT;

	/* It's possible to have no frames pending even if TXE
	 * is set. To indicate that q has not stopped return
	 * true */
	if (!pending && AR5K_REG_READ_Q(ah, AR5K_QCU_TXE, queue))
		return true;

	return pending;
}