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
struct of_phandle_args {int* args; struct device_node* np; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int IMX6QDL_CLK_END ; 
 int IMX6QDL_CLK_LDB_DI0_SEL ; 
 int IMX6QDL_CLK_LDB_DI1_SEL ; 
 int ldb_di_sel_by_clock_id (int) ; 
 int of_count_phandle_with_args (struct device_node*,char*,char*) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static void of_assigned_ldb_sels(struct device_node *node,
				 unsigned int *ldb_di0_sel,
				 unsigned int *ldb_di1_sel)
{
	struct of_phandle_args clkspec;
	int index, rc, num_parents;
	int parent, child, sel;

	num_parents = of_count_phandle_with_args(node, "assigned-clock-parents",
						 "#clock-cells");
	for (index = 0; index < num_parents; index++) {
		rc = of_parse_phandle_with_args(node, "assigned-clock-parents",
					"#clock-cells", index, &clkspec);
		if (rc < 0) {
			/* skip empty (null) phandles */
			if (rc == -ENOENT)
				continue;
			else
				return;
		}
		if (clkspec.np != node || clkspec.args[0] >= IMX6QDL_CLK_END) {
			pr_err("ccm: parent clock %d not in ccm\n", index);
			return;
		}
		parent = clkspec.args[0];

		rc = of_parse_phandle_with_args(node, "assigned-clocks",
				"#clock-cells", index, &clkspec);
		if (rc < 0)
			return;
		if (clkspec.np != node || clkspec.args[0] >= IMX6QDL_CLK_END) {
			pr_err("ccm: child clock %d not in ccm\n", index);
			return;
		}
		child = clkspec.args[0];

		if (child != IMX6QDL_CLK_LDB_DI0_SEL &&
		    child != IMX6QDL_CLK_LDB_DI1_SEL)
			continue;

		sel = ldb_di_sel_by_clock_id(parent);
		if (sel < 0) {
			pr_err("ccm: invalid ldb_di%d parent clock: %d\n",
			       child == IMX6QDL_CLK_LDB_DI1_SEL, parent);
			continue;
		}

		if (child == IMX6QDL_CLK_LDB_DI0_SEL)
			*ldb_di0_sel = sel;
		if (child == IMX6QDL_CLK_LDB_DI1_SEL)
			*ldb_di1_sel = sel;
	}
}