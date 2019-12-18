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
struct dm_snapshot {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __invalidate_snapshot (struct dm_snapshot*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void invalidate_snapshot(struct dm_snapshot *s, int err)
{
	down_write(&s->lock);
	__invalidate_snapshot(s, err);
	up_write(&s->lock);
}