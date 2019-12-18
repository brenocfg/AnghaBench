#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ current_state; } ;
struct sdma_engine {int /*<<< orphan*/  tail_lock; int /*<<< orphan*/  head_lock; TYPE_1__ state; } ;
typedef  enum sdma_events { ____Placeholder_sdma_events } sdma_events ;

/* Variables and functions */
 int /*<<< orphan*/  __sdma_process_event (struct sdma_engine*,int) ; 
 int /*<<< orphan*/  sdma_desc_avail (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_descq_freecnt (struct sdma_engine*) ; 
 scalar_t__ sdma_state_s99_running ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdma_process_event(struct sdma_engine *sde, enum sdma_events event)
{
	unsigned long flags;

	spin_lock_irqsave(&sde->tail_lock, flags);
	write_seqlock(&sde->head_lock);

	__sdma_process_event(sde, event);

	if (sde->state.current_state == sdma_state_s99_running)
		sdma_desc_avail(sde, sdma_descq_freecnt(sde));

	write_sequnlock(&sde->head_lock);
	spin_unlock_irqrestore(&sde->tail_lock, flags);
}