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
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct device_node {struct device_node* sibling; struct device_node* child; } ;
struct ata_port {TYPE_1__* host; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct ata_port** ports; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ata_port* ata_shost_to_port (struct Scsi_Host*) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* pci_device_to_OF_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,struct device_node*) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int k2_sata_show_info(struct seq_file *m, struct Scsi_Host *shost)
{
	struct ata_port *ap;
	struct device_node *np;
	int index;

	/* Find  the ata_port */
	ap = ata_shost_to_port(shost);
	if (ap == NULL)
		return 0;

	/* Find the OF node for the PCI device proper */
	np = pci_device_to_OF_node(to_pci_dev(ap->host->dev));
	if (np == NULL)
		return 0;

	/* Match it to a port node */
	index = (ap == ap->host->ports[0]) ? 0 : 1;
	for (np = np->child; np != NULL; np = np->sibling) {
		const u32 *reg = of_get_property(np, "reg", NULL);
		if (!reg)
			continue;
		if (index == *reg) {
			seq_printf(m, "devspec: %pOF\n", np);
			break;
		}
	}
	return 0;
}