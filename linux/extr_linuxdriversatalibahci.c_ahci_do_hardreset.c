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
typedef  int /*<<< orphan*/  u8 ;
struct ata_taskfile {int /*<<< orphan*/  command; } ;
struct ata_port {TYPE_1__* host; struct ahci_port_priv* private_data; } ;
struct ata_link {int /*<<< orphan*/  device; struct ata_port* ap; int /*<<< orphan*/  eh_context; } ;
struct ahci_port_priv {int /*<<< orphan*/ * rx_fis; } ;
struct ahci_host_priv {int /*<<< orphan*/  (* start_engine ) (struct ata_port*) ;int /*<<< orphan*/  (* stop_engine ) (struct ata_port*) ;} ;
struct TYPE_2__ {struct ahci_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BUSY ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int RX_FIS_D2H_REG ; 
 int /*<<< orphan*/  ahci_check_ready ; 
 unsigned int ahci_dev_classify (struct ata_port*) ; 
 int /*<<< orphan*/  ata_tf_init (int /*<<< orphan*/ ,struct ata_taskfile*) ; 
 int /*<<< orphan*/  ata_tf_to_fis (struct ata_taskfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long* sata_ehc_deb_timing (int /*<<< orphan*/ *) ; 
 int sata_link_hardreset (struct ata_link*,unsigned long const*,unsigned long,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*) ; 

int ahci_do_hardreset(struct ata_link *link, unsigned int *class,
		      unsigned long deadline, bool *online)
{
	const unsigned long *timing = sata_ehc_deb_timing(&link->eh_context);
	struct ata_port *ap = link->ap;
	struct ahci_port_priv *pp = ap->private_data;
	struct ahci_host_priv *hpriv = ap->host->private_data;
	u8 *d2h_fis = pp->rx_fis + RX_FIS_D2H_REG;
	struct ata_taskfile tf;
	int rc;

	DPRINTK("ENTER\n");

	hpriv->stop_engine(ap);

	/* clear D2H reception area to properly wait for D2H FIS */
	ata_tf_init(link->device, &tf);
	tf.command = ATA_BUSY;
	ata_tf_to_fis(&tf, 0, 0, d2h_fis);

	rc = sata_link_hardreset(link, timing, deadline, online,
				 ahci_check_ready);

	hpriv->start_engine(ap);

	if (*online)
		*class = ahci_dev_classify(ap);

	DPRINTK("EXIT, rc=%d, class=%u\n", rc, *class);
	return rc;
}