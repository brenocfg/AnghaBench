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
struct timer_list {int dummy; } ;
struct ene_device {int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 struct ene_device* dev ; 
 int /*<<< orphan*/  ene_tx_sample (struct ene_device*) ; 
 struct ene_device* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_sim_timer ; 

__attribute__((used)) static void ene_tx_irqsim(struct timer_list *t)
{
	struct ene_device *dev = from_timer(dev, t, tx_sim_timer);
	unsigned long flags;

	spin_lock_irqsave(&dev->hw_lock, flags);
	ene_tx_sample(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);
}