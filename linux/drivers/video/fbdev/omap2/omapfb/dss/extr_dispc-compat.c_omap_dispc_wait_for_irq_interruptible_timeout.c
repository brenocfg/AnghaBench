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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 long ERESTARTSYS ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  dispc_irq_wait_handler ; 
 int omap_dispc_register_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dispc_unregister_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,unsigned long) ; 

int omap_dispc_wait_for_irq_interruptible_timeout(u32 irqmask,
		unsigned long timeout)
{

	int r;
	long time_left;
	DECLARE_COMPLETION_ONSTACK(completion);

	r = omap_dispc_register_isr(dispc_irq_wait_handler, &completion,
			irqmask);

	if (r)
		return r;

	time_left = wait_for_completion_interruptible_timeout(&completion,
			timeout);

	omap_dispc_unregister_isr(dispc_irq_wait_handler, &completion, irqmask);

	if (time_left == 0)
		return -ETIMEDOUT;

	if (time_left == -ERESTARTSYS)
		return -ERESTARTSYS;

	return 0;
}