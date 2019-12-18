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
struct seq_file {struct dss_device* private; } ;
struct dss_device {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_dump_clocks (int /*<<< orphan*/ ,struct seq_file*) ; 
 int /*<<< orphan*/  dss_dump_clocks (struct dss_device*,struct seq_file*) ; 

__attribute__((used)) static int dss_debug_dump_clocks(struct seq_file *s, void *p)
{
	struct dss_device *dss = s->private;

	dss_dump_clocks(dss, s);
	dispc_dump_clocks(dss->dispc, s);
	return 0;
}