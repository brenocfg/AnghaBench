#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct watchdog_pretimeout {struct watchdog_device* wdd; int /*<<< orphan*/  entry; } ;
struct watchdog_device {int /*<<< orphan*/  gov; TYPE_1__* info; } ;
struct TYPE_2__ {int options; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WDIOF_PRETIMEOUT ; 
 int /*<<< orphan*/  default_gov ; 
 struct watchdog_pretimeout* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pretimeout_list ; 
 int /*<<< orphan*/  pretimeout_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int watchdog_register_pretimeout(struct watchdog_device *wdd)
{
	struct watchdog_pretimeout *p;

	if (!(wdd->info->options & WDIOF_PRETIMEOUT))
		return 0;

	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	spin_lock_irq(&pretimeout_lock);
	list_add(&p->entry, &pretimeout_list);
	p->wdd = wdd;
	wdd->gov = default_gov;
	spin_unlock_irq(&pretimeout_lock);

	return 0;
}