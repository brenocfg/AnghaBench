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
struct dm_target {scalar_t__ private; } ;
struct dm_integrity_c {scalar_t__ provided_data_sectors; TYPE_1__* sb; int /*<<< orphan*/  recalc_work; scalar_t__ recalc_wq; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  recalc_sector; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_FLAG_RECALCULATING ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recalc_write_super (struct dm_integrity_c*) ; 
 int /*<<< orphan*/  replay_journal (struct dm_integrity_c*) ; 

__attribute__((used)) static void dm_integrity_resume(struct dm_target *ti)
{
	struct dm_integrity_c *ic = (struct dm_integrity_c *)ti->private;

	replay_journal(ic);

	if (ic->recalc_wq && ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING)) {
		__u64 recalc_pos = le64_to_cpu(ic->sb->recalc_sector);
		if (recalc_pos < ic->provided_data_sectors) {
			queue_work(ic->recalc_wq, &ic->recalc_work);
		} else if (recalc_pos > ic->provided_data_sectors) {
			ic->sb->recalc_sector = cpu_to_le64(ic->provided_data_sectors);
			recalc_write_super(ic);
		}
	}
}