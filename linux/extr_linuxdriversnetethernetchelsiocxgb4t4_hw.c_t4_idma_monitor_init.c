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
struct sge_idma_monitor_state {int idma_1s_thresh; scalar_t__* idma_stalled; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int core_ticks_per_usec (struct adapter*) ; 

void t4_idma_monitor_init(struct adapter *adapter,
			  struct sge_idma_monitor_state *idma)
{
	/* Initialize the state variables for detecting an SGE Ingress DMA
	 * hang.  The SGE has internal counters which count up on each clock
	 * tick whenever the SGE finds its Ingress DMA State Engines in the
	 * same state they were on the previous clock tick.  The clock used is
	 * the Core Clock so we have a limit on the maximum "time" they can
	 * record; typically a very small number of seconds.  For instance,
	 * with a 600MHz Core Clock, we can only count up to a bit more than
	 * 7s.  So we'll synthesize a larger counter in order to not run the
	 * risk of having the "timers" overflow and give us the flexibility to
	 * maintain a Hung SGE State Machine of our own which operates across
	 * a longer time frame.
	 */
	idma->idma_1s_thresh = core_ticks_per_usec(adapter) * 1000000; /* 1s */
	idma->idma_stalled[0] = 0;
	idma->idma_stalled[1] = 0;
}