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
struct TYPE_3__ {int regmapid; } ;
struct ddb_link {TYPE_2__* dev; int /*<<< orphan*/  temp_lock; TYPE_1__ ids; struct ddb_info* info; } ;
struct ddb_info {scalar_t__ type; int /*<<< orphan*/  tempmon_irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DDB_OCTOPUS_MAX_CT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int tempmon_init (struct ddb_link*,int) ; 

__attribute__((used)) static int ddb_init_tempmon(struct ddb_link *link)
{
	const struct ddb_info *info = link->info;

	if (!info->tempmon_irq)
		return 0;
	if (info->type == DDB_OCTOPUS_MAX_CT)
		if (link->ids.regmapid < 0x00010002)
			return 0;
	spin_lock_init(&link->temp_lock);
	dev_dbg(link->dev->dev, "init_tempmon\n");
	return tempmon_init(link, 1);
}