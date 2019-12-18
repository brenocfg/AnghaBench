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
struct TYPE_2__ {int /*<<< orphan*/  fc_row_file; int /*<<< orphan*/  fc_normal_file; int /*<<< orphan*/  fc_clear; int /*<<< orphan*/  fc_trace; } ;

/* Variables and functions */
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* fc_trc_flag ; 
 void* fnic_fc_rdata_trace_debugfs_file ; 
 void* fnic_fc_trace_clear ; 
 void* fnic_fc_trace_debugfs_file ; 
 void* fnic_fc_trace_enable ; 
 int /*<<< orphan*/  fnic_trace_ctrl_fops ; 
 int /*<<< orphan*/  fnic_trace_debugfs_fops ; 
 int /*<<< orphan*/  fnic_trace_debugfs_root ; 

void fnic_fc_trace_debugfs_init(void)
{
	fnic_fc_trace_enable = debugfs_create_file("fc_trace_enable",
					S_IFREG|S_IRUGO|S_IWUSR,
					fnic_trace_debugfs_root,
					&(fc_trc_flag->fc_trace),
					&fnic_trace_ctrl_fops);

	fnic_fc_trace_clear = debugfs_create_file("fc_trace_clear",
					S_IFREG|S_IRUGO|S_IWUSR,
					fnic_trace_debugfs_root,
					&(fc_trc_flag->fc_clear),
					&fnic_trace_ctrl_fops);

	fnic_fc_rdata_trace_debugfs_file =
		debugfs_create_file("fc_trace_rdata",
				    S_IFREG|S_IRUGO|S_IWUSR,
				    fnic_trace_debugfs_root,
				    &(fc_trc_flag->fc_normal_file),
				    &fnic_trace_debugfs_fops);

	fnic_fc_trace_debugfs_file =
		debugfs_create_file("fc_trace",
				    S_IFREG|S_IRUGO|S_IWUSR,
				    fnic_trace_debugfs_root,
				    &(fc_trc_flag->fc_row_file),
				    &fnic_trace_debugfs_fops);
}