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

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnic_fc_rdata_trace_debugfs_file ; 
 int /*<<< orphan*/ * fnic_fc_trace_clear ; 
 int /*<<< orphan*/ * fnic_fc_trace_debugfs_file ; 
 int /*<<< orphan*/ * fnic_fc_trace_enable ; 

void fnic_fc_trace_debugfs_terminate(void)
{
	debugfs_remove(fnic_fc_trace_debugfs_file);
	fnic_fc_trace_debugfs_file = NULL;

	debugfs_remove(fnic_fc_rdata_trace_debugfs_file);
	fnic_fc_rdata_trace_debugfs_file = NULL;

	debugfs_remove(fnic_fc_trace_enable);
	fnic_fc_trace_enable = NULL;

	debugfs_remove(fnic_fc_trace_clear);
	fnic_fc_trace_clear = NULL;
}