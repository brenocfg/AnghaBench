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
struct pgpath {int dummy; } ;
struct multipath {scalar_t__ pg_init_retries; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  pg_init_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPATHF_PG_INIT_DISABLED ; 
 int /*<<< orphan*/  MPATHF_PG_INIT_REQUIRED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool pg_init_limit_reached(struct multipath *m, struct pgpath *pgpath)
{
	unsigned long flags;
	bool limit_reached = false;

	spin_lock_irqsave(&m->lock, flags);

	if (atomic_read(&m->pg_init_count) <= m->pg_init_retries &&
	    !test_bit(MPATHF_PG_INIT_DISABLED, &m->flags))
		set_bit(MPATHF_PG_INIT_REQUIRED, &m->flags);
	else
		limit_reached = true;

	spin_unlock_irqrestore(&m->lock, flags);

	return limit_reached;
}