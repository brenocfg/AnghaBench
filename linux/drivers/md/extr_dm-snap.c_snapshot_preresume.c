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
struct dm_snapshot {int /*<<< orphan*/  lock; int /*<<< orphan*/  ti; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  __find_snapshots_sharing_cow (struct dm_snapshot*,struct dm_snapshot**,struct dm_snapshot**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  dm_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snapshot_preresume(struct dm_target *ti)
{
	int r = 0;
	struct dm_snapshot *s = ti->private;
	struct dm_snapshot *snap_src = NULL, *snap_dest = NULL;

	down_read(&_origins_lock);
	(void) __find_snapshots_sharing_cow(s, &snap_src, &snap_dest, NULL);
	if (snap_src && snap_dest) {
		down_read(&snap_src->lock);
		if (s == snap_src) {
			DMERR("Unable to resume snapshot source until "
			      "handover completes.");
			r = -EINVAL;
		} else if (!dm_suspended(snap_src->ti)) {
			DMERR("Unable to perform snapshot handover until "
			      "source is suspended.");
			r = -EINVAL;
		}
		up_read(&snap_src->lock);
	}
	up_read(&_origins_lock);

	return r;
}