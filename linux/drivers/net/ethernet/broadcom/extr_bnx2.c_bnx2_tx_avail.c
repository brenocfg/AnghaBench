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
struct bnx2_tx_ring_info {int /*<<< orphan*/  tx_cons; int /*<<< orphan*/  tx_prod; } ;
struct bnx2 {int tx_ring_size; } ;

/* Variables and functions */
 int BNX2_MAX_TX_DESC_CNT ; 
 int BNX2_TX_DESC_CNT ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u32 bnx2_tx_avail(struct bnx2 *bp, struct bnx2_tx_ring_info *txr)
{
	u32 diff;

	/* The ring uses 256 indices for 255 entries, one of them
	 * needs to be skipped.
	 */
	diff = READ_ONCE(txr->tx_prod) - READ_ONCE(txr->tx_cons);
	if (unlikely(diff >= BNX2_TX_DESC_CNT)) {
		diff &= 0xffff;
		if (diff == BNX2_TX_DESC_CNT)
			diff = BNX2_MAX_TX_DESC_CNT;
	}
	return bp->tx_ring_size - diff;
}