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
struct multipath {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct dm_target {struct multipath* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPATHF_QUEUE_IF_NO_PATH ; 
 int /*<<< orphan*/  MPATHF_SAVED_QUEUE_IF_NO_PATH ; 
 int /*<<< orphan*/  assign_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void multipath_resume(struct dm_target *ti)
{
	struct multipath *m = ti->private;
	unsigned long flags;

	spin_lock_irqsave(&m->lock, flags);
	assign_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags,
		   test_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &m->flags));
	spin_unlock_irqrestore(&m->lock, flags);
}