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
typedef  size_t u32 ;
struct ath_hw {struct ath9k_tx_queue_info* txq; } ;
struct ath_common {int dummy; } ;
struct ath9k_tx_queue_info {scalar_t__ tqi_type; } ;

/* Variables and functions */
 scalar_t__ ATH9K_TX_QUEUE_INACTIVE ; 
 int /*<<< orphan*/  QUEUE ; 
 int /*<<< orphan*/  ath9k_hw_clear_queue_interrupts (struct ath_hw*,size_t) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_txq_interrupts (struct ath_hw*,struct ath9k_tx_queue_info*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,size_t) ; 

bool ath9k_hw_releasetxqueue(struct ath_hw *ah, u32 q)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_tx_queue_info *qi;

	qi = &ah->txq[q];
	if (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) {
		ath_dbg(common, QUEUE, "Release TXQ, inactive queue: %u\n", q);
		return false;
	}

	ath_dbg(common, QUEUE, "Release TX queue: %u\n", q);

	qi->tqi_type = ATH9K_TX_QUEUE_INACTIVE;
	ath9k_hw_clear_queue_interrupts(ah, q);
	ath9k_hw_set_txq_interrupts(ah, qi);

	return true;
}