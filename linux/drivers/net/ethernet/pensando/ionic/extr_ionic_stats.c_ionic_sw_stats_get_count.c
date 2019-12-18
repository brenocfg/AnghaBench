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
typedef  int u64 ;
struct ionic_lif {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_LIF_SW_DEBUG_STATS ; 
 int /*<<< orphan*/  IONIC_LIF_UP ; 
 int IONIC_MAX_NUM_NAPI_CNTR ; 
 int IONIC_MAX_NUM_SG_CNTR ; 
 int IONIC_NUM_DBG_CQ_STATS ; 
 int IONIC_NUM_DBG_INTR_STATS ; 
 int IONIC_NUM_DBG_NAPI_STATS ; 
 scalar_t__ IONIC_NUM_LIF_STATS ; 
 int IONIC_NUM_RX_STATS ; 
 int IONIC_NUM_TX_Q_STATS ; 
 int IONIC_NUM_TX_STATS ; 
 int MAX_Q (struct ionic_lif*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 ionic_sw_stats_get_count(struct ionic_lif *lif)
{
	u64 total = 0;

	/* lif stats */
	total += IONIC_NUM_LIF_STATS;

	/* tx stats */
	total += MAX_Q(lif) * IONIC_NUM_TX_STATS;

	/* rx stats */
	total += MAX_Q(lif) * IONIC_NUM_RX_STATS;

	if (test_bit(IONIC_LIF_UP, lif->state) &&
	    test_bit(IONIC_LIF_SW_DEBUG_STATS, lif->state)) {
		/* tx debug stats */
		total += MAX_Q(lif) * (IONIC_NUM_DBG_CQ_STATS +
				      IONIC_NUM_TX_Q_STATS +
				      IONIC_NUM_DBG_INTR_STATS +
				      IONIC_MAX_NUM_SG_CNTR);

		/* rx debug stats */
		total += MAX_Q(lif) * (IONIC_NUM_DBG_CQ_STATS +
				      IONIC_NUM_DBG_INTR_STATS +
				      IONIC_NUM_DBG_NAPI_STATS +
				      IONIC_MAX_NUM_NAPI_CNTR);
	}

	return total;
}