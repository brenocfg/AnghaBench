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
struct fc_exch {int /*<<< orphan*/  ex_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_exch_timer_set_locked (struct fc_exch*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_exch_timer_set(struct fc_exch *ep, unsigned int timer_msec)
{
	spin_lock_bh(&ep->ex_lock);
	fc_exch_timer_set_locked(ep, timer_msec);
	spin_unlock_bh(&ep->ex_lock);
}