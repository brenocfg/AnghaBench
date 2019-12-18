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
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stop_merge (struct dm_snapshot*) ; 

__attribute__((used)) static void snapshot_merge_presuspend(struct dm_target *ti)
{
	struct dm_snapshot *s = ti->private;

	stop_merge(s);
}