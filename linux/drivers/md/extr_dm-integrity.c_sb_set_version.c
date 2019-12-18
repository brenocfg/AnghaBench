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
struct dm_integrity_c {char mode; TYPE_1__* sb; scalar_t__ meta_dev; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_FLAG_DIRTY_BITMAP ; 
 int /*<<< orphan*/  SB_FLAG_RECALCULATING ; 
 int /*<<< orphan*/  SB_VERSION_1 ; 
 int /*<<< orphan*/  SB_VERSION_2 ; 
 int /*<<< orphan*/  SB_VERSION_3 ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sb_set_version(struct dm_integrity_c *ic)
{
	if (ic->mode == 'B' || ic->sb->flags & cpu_to_le32(SB_FLAG_DIRTY_BITMAP))
		ic->sb->version = SB_VERSION_3;
	else if (ic->meta_dev || ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING))
		ic->sb->version = SB_VERSION_2;
	else
		ic->sb->version = SB_VERSION_1;
}