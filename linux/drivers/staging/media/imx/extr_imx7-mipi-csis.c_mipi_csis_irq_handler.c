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
typedef  int u32 ;
struct csi_state {int /*<<< orphan*/  slock; TYPE_1__* events; scalar_t__ debug; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int mask; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MIPI_CSIS_INTSRC ; 
 int MIPI_CSIS_INTSRC_ERRORS ; 
 unsigned int MIPI_CSIS_NUM_EVENTS ; 
 int mipi_csis_read (struct csi_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_csis_write (struct csi_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t mipi_csis_irq_handler(int irq, void *dev_id)
{
	struct csi_state *state = dev_id;
	unsigned long flags;
	unsigned int i;
	u32 status;

	status = mipi_csis_read(state, MIPI_CSIS_INTSRC);

	spin_lock_irqsave(&state->slock, flags);

	/* Update the event/error counters */
	if ((status & MIPI_CSIS_INTSRC_ERRORS) || state->debug) {
		for (i = 0; i < MIPI_CSIS_NUM_EVENTS; i++) {
			if (!(status & state->events[i].mask))
				continue;
			state->events[i].counter++;
		}
	}
	spin_unlock_irqrestore(&state->slock, flags);

	mipi_csis_write(state, MIPI_CSIS_INTSRC, status);

	return IRQ_HANDLED;
}