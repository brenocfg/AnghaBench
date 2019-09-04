#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_3__ {int near_copies; int raid_disks; int far_copies; int far_set_size; scalar_t__ far_offset; } ;
struct r10conf {TYPE_2__* mirrors; TYPE_1__ geo; } ;
struct mddev {int chunk_sectors; scalar_t__ degraded; struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  In_sync ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid10_status(struct seq_file *seq, struct mddev *mddev)
{
	struct r10conf *conf = mddev->private;
	int i;

	if (conf->geo.near_copies < conf->geo.raid_disks)
		seq_printf(seq, " %dK chunks", mddev->chunk_sectors / 2);
	if (conf->geo.near_copies > 1)
		seq_printf(seq, " %d near-copies", conf->geo.near_copies);
	if (conf->geo.far_copies > 1) {
		if (conf->geo.far_offset)
			seq_printf(seq, " %d offset-copies", conf->geo.far_copies);
		else
			seq_printf(seq, " %d far-copies", conf->geo.far_copies);
		if (conf->geo.far_set_size != conf->geo.raid_disks)
			seq_printf(seq, " %d devices per set", conf->geo.far_set_size);
	}
	seq_printf(seq, " [%d/%d] [", conf->geo.raid_disks,
					conf->geo.raid_disks - mddev->degraded);
	rcu_read_lock();
	for (i = 0; i < conf->geo.raid_disks; i++) {
		struct md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		seq_printf(seq, "%s", rdev && test_bit(In_sync, &rdev->flags) ? "U" : "_");
	}
	rcu_read_unlock();
	seq_printf(seq, "]");
}