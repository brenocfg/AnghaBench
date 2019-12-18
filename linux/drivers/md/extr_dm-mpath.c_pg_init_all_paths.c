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
struct multipath {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __pg_init_all_paths (struct multipath*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pg_init_all_paths(struct multipath *m)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&m->lock, flags);
	ret = __pg_init_all_paths(m);
	spin_unlock_irqrestore(&m->lock, flags);

	return ret;
}