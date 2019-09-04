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
struct cyttsp {int /*<<< orphan*/  irq; int /*<<< orphan*/  state; int /*<<< orphan*/  bl_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  CY_BL_STATE ; 
 int CY_DELAY_DFLT ; 
 int CY_DELAY_MAX ; 
 int /*<<< orphan*/  CY_IDLE_STATE ; 
 int /*<<< orphan*/  CY_SOFT_RESET_MODE ; 
 int EIO ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int ttsp_send_command (struct cyttsp*,int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyttsp_soft_reset(struct cyttsp *ts)
{
	unsigned long timeout;
	int retval;

	/* wait for interrupt to set ready completion */
	reinit_completion(&ts->bl_ready);
	ts->state = CY_BL_STATE;

	enable_irq(ts->irq);

	retval = ttsp_send_command(ts, CY_SOFT_RESET_MODE);
	if (retval)
		goto out;

	timeout = wait_for_completion_timeout(&ts->bl_ready,
			msecs_to_jiffies(CY_DELAY_DFLT * CY_DELAY_MAX));
	retval = timeout ? 0 : -EIO;

out:
	ts->state = CY_IDLE_STATE;
	disable_irq(ts->irq);
	return retval;
}