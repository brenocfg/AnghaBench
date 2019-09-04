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
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  unit_mask; int /*<<< orphan*/  exl; int /*<<< orphan*/  user; int /*<<< orphan*/  kernel; int /*<<< orphan*/  count; int /*<<< orphan*/  event; int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {int num_counters; } ;

/* Variables and functions */
 TYPE_2__* ctr ; 
 TYPE_1__* model ; 
 int /*<<< orphan*/  oprofilefs_create_ulong (struct dentry*,char*,int /*<<< orphan*/ *) ; 
 struct dentry* oprofilefs_mkdir (struct dentry*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int op_mips_create_files(struct dentry *root)
{
	int i;

	for (i = 0; i < model->num_counters; ++i) {
		struct dentry *dir;
		char buf[4];

		snprintf(buf, sizeof buf, "%d", i);
		dir = oprofilefs_mkdir(root, buf);

		oprofilefs_create_ulong(dir, "enabled", &ctr[i].enabled);
		oprofilefs_create_ulong(dir, "event", &ctr[i].event);
		oprofilefs_create_ulong(dir, "count", &ctr[i].count);
		oprofilefs_create_ulong(dir, "kernel", &ctr[i].kernel);
		oprofilefs_create_ulong(dir, "user", &ctr[i].user);
		oprofilefs_create_ulong(dir, "exl", &ctr[i].exl);
		/* Dummy.  */
		oprofilefs_create_ulong(dir, "unit_mask", &ctr[i].unit_mask);
	}

	return 0;
}