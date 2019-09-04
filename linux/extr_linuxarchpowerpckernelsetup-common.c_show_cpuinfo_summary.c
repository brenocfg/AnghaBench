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
struct seq_file {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {char const* name; int /*<<< orphan*/  (* show_cpuinfo ) (struct seq_file*) ;} ;

/* Variables and functions */
 struct device_node* of_find_node_by_path (char*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 TYPE_1__ ppc_md ; 
 char const* ppc_tb_freq ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*) ; 
 int /*<<< orphan*/  stub1 (struct seq_file*) ; 

__attribute__((used)) static void show_cpuinfo_summary(struct seq_file *m)
{
	struct device_node *root;
	const char *model = NULL;
#if defined(CONFIG_SMP) && defined(CONFIG_PPC32)
	unsigned long bogosum = 0;
	int i;
	for_each_online_cpu(i)
		bogosum += loops_per_jiffy;
	seq_printf(m, "total bogomips\t: %lu.%02lu\n",
		   bogosum/(500000/HZ), bogosum/(5000/HZ) % 100);
#endif /* CONFIG_SMP && CONFIG_PPC32 */
	seq_printf(m, "timebase\t: %lu\n", ppc_tb_freq);
	if (ppc_md.name)
		seq_printf(m, "platform\t: %s\n", ppc_md.name);
	root = of_find_node_by_path("/");
	if (root)
		model = of_get_property(root, "model", NULL);
	if (model)
		seq_printf(m, "model\t\t: %s\n", model);
	of_node_put(root);

	if (ppc_md.show_cpuinfo != NULL)
		ppc_md.show_cpuinfo(m);

#ifdef CONFIG_PPC32
	/* Display the amount of memory */
	seq_printf(m, "Memory\t\t: %d MB\n",
		   (unsigned int)(total_memory / (1024 * 1024)));
#endif
}