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
struct b44 {int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  b44_check_phy (struct b44*) ; 
 int /*<<< orphan*/  b44_stats_update (struct b44*) ; 
 struct b44* bp ; 
 struct b44* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void b44_timer(struct timer_list *t)
{
	struct b44 *bp = from_timer(bp, t, timer);

	spin_lock_irq(&bp->lock);

	b44_check_phy(bp);

	b44_stats_update(bp);

	spin_unlock_irq(&bp->lock);

	mod_timer(&bp->timer, round_jiffies(jiffies + HZ));
}