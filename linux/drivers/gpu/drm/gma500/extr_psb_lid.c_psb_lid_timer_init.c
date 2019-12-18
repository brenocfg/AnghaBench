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
struct timer_list {scalar_t__ expires; } ;
struct drm_psb_private {int /*<<< orphan*/  lid_lock; struct timer_list lid_timer; } ;

/* Variables and functions */
 scalar_t__ PSB_LID_DELAY ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  psb_lid_timer_func ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void psb_lid_timer_init(struct drm_psb_private *dev_priv)
{
	struct timer_list *lid_timer = &dev_priv->lid_timer;
	unsigned long irq_flags;

	spin_lock_init(&dev_priv->lid_lock);
	spin_lock_irqsave(&dev_priv->lid_lock, irq_flags);

	timer_setup(lid_timer, psb_lid_timer_func, 0);

	lid_timer->expires = jiffies + PSB_LID_DELAY;

	add_timer(lid_timer);
	spin_unlock_irqrestore(&dev_priv->lid_lock, irq_flags);
}