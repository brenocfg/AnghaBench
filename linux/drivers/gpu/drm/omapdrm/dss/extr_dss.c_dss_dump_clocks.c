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
struct seq_file {int dummy; } ;
struct dss_device {int /*<<< orphan*/  dss_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_CLK_SRC_FCK ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 char* dss_get_clk_source_name (int /*<<< orphan*/ ) ; 
 scalar_t__ dss_runtime_get (struct dss_device*) ; 
 int /*<<< orphan*/  dss_runtime_put (struct dss_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void dss_dump_clocks(struct dss_device *dss, struct seq_file *s)
{
	const char *fclk_name;
	unsigned long fclk_rate;

	if (dss_runtime_get(dss))
		return;

	seq_printf(s, "- DSS -\n");

	fclk_name = dss_get_clk_source_name(DSS_CLK_SRC_FCK);
	fclk_rate = clk_get_rate(dss->dss_clk);

	seq_printf(s, "%s = %lu\n",
			fclk_name,
			fclk_rate);

	dss_runtime_put(dss);
}