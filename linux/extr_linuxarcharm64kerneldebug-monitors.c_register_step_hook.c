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
struct step_hook {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  step_hook ; 
 int /*<<< orphan*/  step_hook_lock ; 

void register_step_hook(struct step_hook *hook)
{
	spin_lock(&step_hook_lock);
	list_add_rcu(&hook->node, &step_hook);
	spin_unlock(&step_hook_lock);
}