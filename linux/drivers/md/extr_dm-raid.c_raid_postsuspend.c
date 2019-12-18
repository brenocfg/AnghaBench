#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  recovery; } ;
struct raid_set {TYPE_1__ md; int /*<<< orphan*/  runtime_flags; } ;
struct dm_target {struct raid_set* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  RT_FLAG_RS_SUSPENDED ; 
 int /*<<< orphan*/  md_stop_writes (TYPE_1__*) ; 
 int /*<<< orphan*/  mddev_lock_nointr (TYPE_1__*) ; 
 int /*<<< orphan*/  mddev_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  mddev_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid_postsuspend(struct dm_target *ti)
{
	struct raid_set *rs = ti->private;

	if (!test_and_set_bit(RT_FLAG_RS_SUSPENDED, &rs->runtime_flags)) {
		/* Writes have to be stopped before suspending to avoid deadlocks. */
		if (!test_bit(MD_RECOVERY_FROZEN, &rs->md.recovery))
			md_stop_writes(&rs->md);

		mddev_lock_nointr(&rs->md);
		mddev_suspend(&rs->md);
		mddev_unlock(&rs->md);
	}
}