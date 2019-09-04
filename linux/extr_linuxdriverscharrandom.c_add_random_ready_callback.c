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
struct random_ready_callback {int /*<<< orphan*/  list; struct module* owner; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int EALREADY ; 
 int ENOENT ; 
 scalar_t__ crng_ready () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  random_ready_list ; 
 int /*<<< orphan*/  random_ready_list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 

int add_random_ready_callback(struct random_ready_callback *rdy)
{
	struct module *owner;
	unsigned long flags;
	int err = -EALREADY;

	if (crng_ready())
		return err;

	owner = rdy->owner;
	if (!try_module_get(owner))
		return -ENOENT;

	spin_lock_irqsave(&random_ready_list_lock, flags);
	if (crng_ready())
		goto out;

	owner = NULL;

	list_add(&rdy->list, &random_ready_list);
	err = 0;

out:
	spin_unlock_irqrestore(&random_ready_list_lock, flags);

	module_put(owner);

	return err;
}