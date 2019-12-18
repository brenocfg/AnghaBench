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
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  user; int /*<<< orphan*/  kernel; int /*<<< orphan*/  unit_mask; int /*<<< orphan*/  count; int /*<<< orphan*/  event; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 TYPE_1__* counter_config ; 
 unsigned int num_counters ; 
 int /*<<< orphan*/  oprofilefs_create_ulong (struct dentry*,char*,int /*<<< orphan*/ *) ; 
 struct dentry* oprofilefs_mkdir (struct dentry*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static int oprofile_perf_create_files(struct dentry *root)
{
	unsigned int i;

	for (i = 0; i < num_counters; i++) {
		struct dentry *dir;
		char buf[4];

		snprintf(buf, sizeof buf, "%d", i);
		dir = oprofilefs_mkdir(root, buf);
		oprofilefs_create_ulong(dir, "enabled", &counter_config[i].enabled);
		oprofilefs_create_ulong(dir, "event", &counter_config[i].event);
		oprofilefs_create_ulong(dir, "count", &counter_config[i].count);
		oprofilefs_create_ulong(dir, "unit_mask", &counter_config[i].unit_mask);
		oprofilefs_create_ulong(dir, "kernel", &counter_config[i].kernel);
		oprofilefs_create_ulong(dir, "user", &counter_config[i].user);
	}

	return 0;
}