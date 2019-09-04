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
struct xgene_ahci_context {unsigned int* class; } ;
struct ata_port {size_t port_no; TYPE_1__* host; } ;
struct ata_link {struct ata_port* ap; } ;
struct ahci_host_priv {struct xgene_ahci_context* plat_data; } ;
struct TYPE_2__ {struct ahci_host_priv* private_data; } ;

/* Variables and functions */
 unsigned int ATA_DEV_PMP ; 
 int PORT_FBS ; 
 int PORT_FBS_DEV_MASK ; 
 int PORT_FBS_DEV_OFFSET ; 
 int /*<<< orphan*/  ahci_check_ready ; 
 int ahci_do_softreset (struct ata_link*,unsigned int*,int,unsigned long,int /*<<< orphan*/ ) ; 
 void* ahci_port_base (struct ata_port*) ; 
 int readl (void*) ; 
 int sata_srst_pmp (struct ata_link*) ; 
 int /*<<< orphan*/  writel (int,void*) ; 

__attribute__((used)) static int xgene_ahci_softreset(struct ata_link *link, unsigned int *class,
			  unsigned long deadline)
{
	int pmp = sata_srst_pmp(link);
	struct ata_port *ap = link->ap;
	struct ahci_host_priv *hpriv = ap->host->private_data;
	struct xgene_ahci_context *ctx = hpriv->plat_data;
	void *port_mmio = ahci_port_base(ap);
	u32 port_fbs;
	u32 port_fbs_save;
	u32 retry = 1;
	u32 rc;

	port_fbs_save = readl(port_mmio + PORT_FBS);

	/*
	 * Set PxFBS.DEV field with pmp
	 * value.
	 */
	port_fbs = readl(port_mmio + PORT_FBS);
	port_fbs &= ~PORT_FBS_DEV_MASK;
	port_fbs |= pmp << PORT_FBS_DEV_OFFSET;
	writel(port_fbs, port_mmio + PORT_FBS);

softreset_retry:
	rc = ahci_do_softreset(link, class, pmp,
			       deadline, ahci_check_ready);

	ctx->class[ap->port_no] = *class;
	if (*class != ATA_DEV_PMP) {
		/*
		 * Retry for normal drives without
		 * setting PxFBS.DEV field with pmp value.
		 */
		if (retry--) {
			writel(port_fbs_save, port_mmio + PORT_FBS);
			goto softreset_retry;
		}
	}

	return rc;
}