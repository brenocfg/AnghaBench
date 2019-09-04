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
struct break_hook {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  break_hook_lock ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void unregister_break_hook(struct break_hook *hook)
{
	spin_lock(&break_hook_lock);
	list_del_rcu(&hook->node);
	spin_unlock(&break_hook_lock);
	synchronize_rcu();
}