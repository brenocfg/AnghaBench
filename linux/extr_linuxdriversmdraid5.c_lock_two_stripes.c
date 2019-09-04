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
struct stripe_head {int /*<<< orphan*/  stripe_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void lock_two_stripes(struct stripe_head *sh1, struct stripe_head *sh2)
{
	if (sh1 > sh2) {
		spin_lock_irq(&sh2->stripe_lock);
		spin_lock_nested(&sh1->stripe_lock, 1);
	} else {
		spin_lock_irq(&sh1->stripe_lock);
		spin_lock_nested(&sh2->stripe_lock, 1);
	}
}