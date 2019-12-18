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
struct sge_idma_monitor_state {int idma_1s_thresh; int* idma_stalled; int* idma_qid; int* idma_warn; int* idma_state; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGE_DEBUG_DATA_HIGH_A ; 
 int /*<<< orphan*/  SGE_DEBUG_DATA_LOW_A ; 
 int /*<<< orphan*/  SGE_DEBUG_INDEX_A ; 
 int SGE_IDMA_WARN_REPEAT ; 
 int SGE_IDMA_WARN_THRESH ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_sge_decode_idma_state (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t4_idma_monitor(struct adapter *adapter,
		     struct sge_idma_monitor_state *idma,
		     int hz, int ticks)
{
	int i, idma_same_state_cnt[2];

	 /* Read the SGE Debug Ingress DMA Same State Count registers.  These
	  * are counters inside the SGE which count up on each clock when the
	  * SGE finds its Ingress DMA State Engines in the same states they
	  * were in the previous clock.  The counters will peg out at
	  * 0xffffffff without wrapping around so once they pass the 1s
	  * threshold they'll stay above that till the IDMA state changes.
	  */
	t4_write_reg(adapter, SGE_DEBUG_INDEX_A, 13);
	idma_same_state_cnt[0] = t4_read_reg(adapter, SGE_DEBUG_DATA_HIGH_A);
	idma_same_state_cnt[1] = t4_read_reg(adapter, SGE_DEBUG_DATA_LOW_A);

	for (i = 0; i < 2; i++) {
		u32 debug0, debug11;

		/* If the Ingress DMA Same State Counter ("timer") is less
		 * than 1s, then we can reset our synthesized Stall Timer and
		 * continue.  If we have previously emitted warnings about a
		 * potential stalled Ingress Queue, issue a note indicating
		 * that the Ingress Queue has resumed forward progress.
		 */
		if (idma_same_state_cnt[i] < idma->idma_1s_thresh) {
			if (idma->idma_stalled[i] >= SGE_IDMA_WARN_THRESH * hz)
				dev_warn(adapter->pdev_dev, "SGE idma%d, queue %u, "
					 "resumed after %d seconds\n",
					 i, idma->idma_qid[i],
					 idma->idma_stalled[i] / hz);
			idma->idma_stalled[i] = 0;
			continue;
		}

		/* Synthesize an SGE Ingress DMA Same State Timer in the Hz
		 * domain.  The first time we get here it'll be because we
		 * passed the 1s Threshold; each additional time it'll be
		 * because the RX Timer Callback is being fired on its regular
		 * schedule.
		 *
		 * If the stall is below our Potential Hung Ingress Queue
		 * Warning Threshold, continue.
		 */
		if (idma->idma_stalled[i] == 0) {
			idma->idma_stalled[i] = hz;
			idma->idma_warn[i] = 0;
		} else {
			idma->idma_stalled[i] += ticks;
			idma->idma_warn[i] -= ticks;
		}

		if (idma->idma_stalled[i] < SGE_IDMA_WARN_THRESH * hz)
			continue;

		/* We'll issue a warning every SGE_IDMA_WARN_REPEAT seconds.
		 */
		if (idma->idma_warn[i] > 0)
			continue;
		idma->idma_warn[i] = SGE_IDMA_WARN_REPEAT * hz;

		/* Read and save the SGE IDMA State and Queue ID information.
		 * We do this every time in case it changes across time ...
		 * can't be too careful ...
		 */
		t4_write_reg(adapter, SGE_DEBUG_INDEX_A, 0);
		debug0 = t4_read_reg(adapter, SGE_DEBUG_DATA_LOW_A);
		idma->idma_state[i] = (debug0 >> (i * 9)) & 0x3f;

		t4_write_reg(adapter, SGE_DEBUG_INDEX_A, 11);
		debug11 = t4_read_reg(adapter, SGE_DEBUG_DATA_LOW_A);
		idma->idma_qid[i] = (debug11 >> (i * 16)) & 0xffff;

		dev_warn(adapter->pdev_dev, "SGE idma%u, queue %u, potentially stuck in "
			 "state %u for %d seconds (debug0=%#x, debug11=%#x)\n",
			 i, idma->idma_qid[i], idma->idma_state[i],
			 idma->idma_stalled[i] / hz,
			 debug0, debug11);
		t4_sge_decode_idma_state(adapter, idma->idma_state[i]);
	}
}