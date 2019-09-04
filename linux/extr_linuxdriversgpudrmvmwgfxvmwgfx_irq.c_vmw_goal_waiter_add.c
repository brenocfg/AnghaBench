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
struct vmw_private {int /*<<< orphan*/  goal_queue_waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_IRQFLAG_FENCE_GOAL ; 
 int /*<<< orphan*/  vmw_generic_waiter_add (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vmw_goal_waiter_add(struct vmw_private *dev_priv)
{
	vmw_generic_waiter_add(dev_priv, SVGA_IRQFLAG_FENCE_GOAL,
			       &dev_priv->goal_queue_waiters);
}