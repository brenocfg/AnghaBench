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
typedef  int u32 ;
struct ata_port {int dummy; } ;
struct ata_link {struct ata_port* ap; } ;

/* Variables and functions */
 int PORT_FBS ; 
 int PORT_FBS_DEV_MASK ; 
 int PORT_FBS_DEV_OFFSET ; 
 int /*<<< orphan*/  ahci_check_ready ; 
 int ahci_do_softreset (struct ata_link*,unsigned int*,int,unsigned long,int /*<<< orphan*/ ) ; 
 void* ahci_port_base (struct ata_port*) ; 
 int readl (void*) ; 
 int sata_srst_pmp (struct ata_link*) ; 
 int /*<<< orphan*/  writel (int,void*) ; 

__attribute__((used)) static int xgene_ahci_pmp_softreset(struct ata_link *link, unsigned int *class,
			  unsigned long deadline)
{
	int pmp = sata_srst_pmp(link);
	struct ata_port *ap = link->ap;
	u32 rc;
	void *port_mmio = ahci_port_base(ap);
	u32 port_fbs;

	/*
	 * Set PxFBS.DEV field with pmp
	 * value.
	 */
	port_fbs = readl(port_mmio + PORT_FBS);
	port_fbs &= ~PORT_FBS_DEV_MASK;
	port_fbs |= pmp << PORT_FBS_DEV_OFFSET;
	writel(port_fbs, port_mmio + PORT_FBS);

	rc = ahci_do_softreset(link, class, pmp, deadline, ahci_check_ready);

	return rc;
}