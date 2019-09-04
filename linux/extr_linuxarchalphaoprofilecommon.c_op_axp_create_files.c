#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  unit_mask; int /*<<< orphan*/  user; int /*<<< orphan*/  kernel; int /*<<< orphan*/  count; int /*<<< orphan*/  event; int /*<<< orphan*/  enabled; } ;
struct TYPE_5__ {int num_counters; scalar_t__ can_set_proc_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable_user; int /*<<< orphan*/  enable_kernel; int /*<<< orphan*/  enable_pal; } ;

/* Variables and functions */
 TYPE_3__* ctr ; 
 TYPE_2__* model ; 
 int /*<<< orphan*/  oprofilefs_create_ulong (struct dentry*,char*,int /*<<< orphan*/ *) ; 
 struct dentry* oprofilefs_mkdir (struct dentry*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 TYPE_1__ sys ; 

__attribute__((used)) static int
op_axp_create_files(struct dentry *root)
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
		/* Dummies.  */
		oprofilefs_create_ulong(dir, "kernel", &ctr[i].kernel);
		oprofilefs_create_ulong(dir, "user", &ctr[i].user);
		oprofilefs_create_ulong(dir, "unit_mask", &ctr[i].unit_mask);
	}

	if (model->can_set_proc_mode) {
		oprofilefs_create_ulong(root, "enable_pal",
					&sys.enable_pal);
		oprofilefs_create_ulong(root, "enable_kernel",
					&sys.enable_kernel);
		oprofilefs_create_ulong(root, "enable_user",
					&sys.enable_user);
	}

	return 0;
}