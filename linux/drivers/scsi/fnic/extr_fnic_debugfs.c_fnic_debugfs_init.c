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
struct fc_trace_flag_type {int fc_normal_file; int fnic_trace; int fc_trace; int fc_clear; scalar_t__ fc_row_file; } ;

/* Variables and functions */
 void* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct fc_trace_flag_type* fc_trc_flag ; 
 void* fnic_stats_debugfs_root ; 
 int /*<<< orphan*/ * fnic_trace_debugfs_root ; 
 scalar_t__ vmalloc (int) ; 

int fnic_debugfs_init(void)
{
	fnic_trace_debugfs_root = debugfs_create_dir("fnic", NULL);

	fnic_stats_debugfs_root = debugfs_create_dir("statistics",
						fnic_trace_debugfs_root);

	/* Allocate memory to structure */
	fc_trc_flag = (struct fc_trace_flag_type *)
		vmalloc(sizeof(struct fc_trace_flag_type));

	if (fc_trc_flag) {
		fc_trc_flag->fc_row_file = 0;
		fc_trc_flag->fc_normal_file = 1;
		fc_trc_flag->fnic_trace = 2;
		fc_trc_flag->fc_trace = 3;
		fc_trc_flag->fc_clear = 4;
	}

	return 0;
}