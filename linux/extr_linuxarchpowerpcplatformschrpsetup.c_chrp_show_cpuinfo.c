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
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ GG2_PCI_CC_CTRL ; 
 scalar_t__ GG2_PCI_DRAM_BANK0 ; 
 scalar_t__ GG2_PCI_DRAM_CTRL ; 
 int /*<<< orphan*/ * gg2_cachemodes ; 
 int* gg2_cachesizes ; 
 char const** gg2_cachetypes ; 
 int /*<<< orphan*/ * gg2_memtypes ; 
 scalar_t__ gg2_pci_config_base ; 
 int in_le32 (scalar_t__) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static void chrp_show_cpuinfo(struct seq_file *m)
{
	int i, sdramen;
	unsigned int t;
	struct device_node *root;
	const char *model = "";

	root = of_find_node_by_path("/");
	if (root)
		model = of_get_property(root, "model", NULL);
	seq_printf(m, "machine\t\t: CHRP %s\n", model);

	/* longtrail (goldengate) stuff */
	if (model && !strncmp(model, "IBM,LongTrail", 13)) {
		/* VLSI VAS96011/12 `Golden Gate 2' */
		/* Memory banks */
		sdramen = (in_le32(gg2_pci_config_base + GG2_PCI_DRAM_CTRL)
			   >>31) & 1;
		for (i = 0; i < (sdramen ? 4 : 6); i++) {
			t = in_le32(gg2_pci_config_base+
						 GG2_PCI_DRAM_BANK0+
						 i*4);
			if (!(t & 1))
				continue;
			switch ((t>>8) & 0x1f) {
			case 0x1f:
				model = "4 MB";
				break;
			case 0x1e:
				model = "8 MB";
				break;
			case 0x1c:
				model = "16 MB";
				break;
			case 0x18:
				model = "32 MB";
				break;
			case 0x10:
				model = "64 MB";
				break;
			case 0x00:
				model = "128 MB";
				break;
			default:
				model = "Reserved";
				break;
			}
			seq_printf(m, "memory bank %d\t: %s %s\n", i, model,
				   gg2_memtypes[sdramen ? 1 : ((t>>1) & 3)]);
		}
		/* L2 cache */
		t = in_le32(gg2_pci_config_base+GG2_PCI_CC_CTRL);
		seq_printf(m, "board l2\t: %s %s (%s)\n",
			   gg2_cachesizes[(t>>7) & 3],
			   gg2_cachetypes[(t>>2) & 3],
			   gg2_cachemodes[t & 3]);
	}
	of_node_put(root);
}