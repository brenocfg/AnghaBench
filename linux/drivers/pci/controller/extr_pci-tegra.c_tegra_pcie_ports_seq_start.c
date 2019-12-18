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
struct tegra_pcie {int /*<<< orphan*/  ports; } ;
struct seq_file {struct tegra_pcie* private; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 void* seq_list_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 

__attribute__((used)) static void *tegra_pcie_ports_seq_start(struct seq_file *s, loff_t *pos)
{
	struct tegra_pcie *pcie = s->private;

	if (list_empty(&pcie->ports))
		return NULL;

	seq_printf(s, "Index  Status\n");

	return seq_list_start(&pcie->ports, *pos);
}