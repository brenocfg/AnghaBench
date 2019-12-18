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
struct seq_file {int dummy; } ;
struct mpconf {int raid_disks; TYPE_1__* multipaths; } ;
struct mddev {scalar_t__ degraded; struct mpconf* private; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  In_sync ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void multipath_status(struct seq_file *seq, struct mddev *mddev)
{
	struct mpconf *conf = mddev->private;
	int i;

	seq_printf (seq, " [%d/%d] [", conf->raid_disks,
		    conf->raid_disks - mddev->degraded);
	rcu_read_lock();
	for (i = 0; i < conf->raid_disks; i++) {
		struct md_rdev *rdev = rcu_dereference(conf->multipaths[i].rdev);
		seq_printf (seq, "%s", rdev && test_bit(In_sync, &rdev->flags) ? "U" : "_");
	}
	rcu_read_unlock();
	seq_putc(seq, ']');
}