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
struct dpu_core_perf {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */

int dpu_core_perf_debugfs_init(struct dpu_core_perf *perf,
		struct dentry *parent)
{
	return 0;
}