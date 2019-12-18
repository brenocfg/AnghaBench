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
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mwifiex_pcie_of_match_table ; 
 int /*<<< orphan*/  of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_pcie_probe_of(struct device *dev)
{
	if (!of_match_node(mwifiex_pcie_of_match_table, dev->of_node)) {
		dev_err(dev, "required compatible string missing\n");
		return -EINVAL;
	}

	return 0;
}