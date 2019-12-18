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
struct ath_hw {int ts_size; int /*<<< orphan*/  ts_paddr_end; int /*<<< orphan*/  ts_paddr_start; scalar_t__ ts_ring; scalar_t__ ts_tail; } ;
struct ar9003_txs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_Q_STATUS_RING_END ; 
 int /*<<< orphan*/  AR_Q_STATUS_RING_START ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMIT ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void ath9k_hw_reset_txstatus_ring(struct ath_hw *ah)
{
	ah->ts_tail = 0;

	memset((void *) ah->ts_ring, 0,
		ah->ts_size * sizeof(struct ar9003_txs));

	ath_dbg(ath9k_hw_common(ah), XMIT,
		"TS Start 0x%x End 0x%x Virt %p, Size %d\n",
		ah->ts_paddr_start, ah->ts_paddr_end,
		ah->ts_ring, ah->ts_size);

	REG_WRITE(ah, AR_Q_STATUS_RING_START, ah->ts_paddr_start);
	REG_WRITE(ah, AR_Q_STATUS_RING_END, ah->ts_paddr_end);
}