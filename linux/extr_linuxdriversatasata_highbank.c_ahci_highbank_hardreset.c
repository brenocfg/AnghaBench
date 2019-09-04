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
typedef  int u32 ;
struct ata_taskfile {int /*<<< orphan*/  command; } ;
struct ata_port {int /*<<< orphan*/  port_no; TYPE_1__* host; struct ahci_port_priv* private_data; } ;
struct ata_link {struct ata_port* ap; int /*<<< orphan*/  device; } ;
struct ahci_port_priv {int /*<<< orphan*/ * rx_fis; } ;
struct ahci_host_priv {int /*<<< orphan*/  (* start_engine ) (struct ata_port*) ;int /*<<< orphan*/  (* stop_engine ) (struct ata_port*) ;} ;
struct TYPE_2__ {struct ahci_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BUSY ; 
 int RX_FIS_D2H_REG ; 
 int /*<<< orphan*/  SCR_STATUS ; 
 unsigned int ahci_dev_classify (struct ata_port*) ; 
 int /*<<< orphan*/  ata_tf_init (int /*<<< orphan*/ ,struct ata_taskfile*) ; 
 int /*<<< orphan*/  ata_tf_to_fis (struct ata_taskfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  highbank_cphy_disable_overrides (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  highbank_cphy_override_lane (int /*<<< orphan*/ ) ; 
 int sata_link_hardreset (struct ata_link*,unsigned long const*,unsigned long,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ sata_scr_read (struct ata_link*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*) ; 

__attribute__((used)) static int ahci_highbank_hardreset(struct ata_link *link, unsigned int *class,
				unsigned long deadline)
{
	static const unsigned long timing[] = { 5, 100, 500};
	struct ata_port *ap = link->ap;
	struct ahci_port_priv *pp = ap->private_data;
	struct ahci_host_priv *hpriv = ap->host->private_data;
	u8 *d2h_fis = pp->rx_fis + RX_FIS_D2H_REG;
	struct ata_taskfile tf;
	bool online;
	u32 sstatus;
	int rc;
	int retry = 100;

	hpriv->stop_engine(ap);

	/* clear D2H reception area to properly wait for D2H FIS */
	ata_tf_init(link->device, &tf);
	tf.command = ATA_BUSY;
	ata_tf_to_fis(&tf, 0, 0, d2h_fis);

	do {
		highbank_cphy_disable_overrides(link->ap->port_no);
		rc = sata_link_hardreset(link, timing, deadline, &online, NULL);
		highbank_cphy_override_lane(link->ap->port_no);

		/* If the status is 1, we are connected, but the link did not
		 * come up. So retry resetting the link again.
		 */
		if (sata_scr_read(link, SCR_STATUS, &sstatus))
			break;
		if (!(sstatus & 0x3))
			break;
	} while (!online && retry--);

	hpriv->start_engine(ap);

	if (online)
		*class = ahci_dev_classify(ap);

	return rc;
}