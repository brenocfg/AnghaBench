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
struct ata_link {int /*<<< orphan*/  eh_context; int /*<<< orphan*/  device; struct ata_port* ap; } ;
struct ahci_port_priv {int /*<<< orphan*/ * rx_fis; } ;
struct ahci_host_priv {int /*<<< orphan*/  (* start_engine ) (struct ata_port*) ;int /*<<< orphan*/  (* stop_engine ) (struct ata_port*) ;} ;
struct TYPE_2__ {struct ahci_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BUSY ; 
 int HZ ; 
 int RX_FIS_D2H_REG ; 
 int /*<<< orphan*/  ahci_check_ready ; 
 int /*<<< orphan*/  ahci_kick_engine (struct ata_port*) ; 
 int /*<<< orphan*/  ata_tf_init (int /*<<< orphan*/ ,struct ata_taskfile*) ; 
 int /*<<< orphan*/  ata_tf_to_fis (struct ata_taskfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ata_wait_after_reset (struct ata_link*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sata_ehc_deb_timing (int /*<<< orphan*/ *) ; 
 int sata_link_hardreset (struct ata_link*,int /*<<< orphan*/ ,unsigned long,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*) ; 

__attribute__((used)) static int ahci_p5wdh_hardreset(struct ata_link *link, unsigned int *class,
				unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct ahci_port_priv *pp = ap->private_data;
	struct ahci_host_priv *hpriv = ap->host->private_data;
	u8 *d2h_fis = pp->rx_fis + RX_FIS_D2H_REG;
	struct ata_taskfile tf;
	bool online;
	int rc;

	hpriv->stop_engine(ap);

	/* clear D2H reception area to properly wait for D2H FIS */
	ata_tf_init(link->device, &tf);
	tf.command = ATA_BUSY;
	ata_tf_to_fis(&tf, 0, 0, d2h_fis);

	rc = sata_link_hardreset(link, sata_ehc_deb_timing(&link->eh_context),
				 deadline, &online, NULL);

	hpriv->start_engine(ap);

	/* The pseudo configuration device on SIMG4726 attached to
	 * ASUS P5W-DH Deluxe doesn't send signature FIS after
	 * hardreset if no device is attached to the first downstream
	 * port && the pseudo device locks up on SRST w/ PMP==0.  To
	 * work around this, wait for !BSY only briefly.  If BSY isn't
	 * cleared, perform CLO and proceed to IDENTIFY (achieved by
	 * ATA_LFLAG_NO_SRST and ATA_LFLAG_ASSUME_ATA).
	 *
	 * Wait for two seconds.  Devices attached to downstream port
	 * which can't process the following IDENTIFY after this will
	 * have to be reset again.  For most cases, this should
	 * suffice while making probing snappish enough.
	 */
	if (online) {
		rc = ata_wait_after_reset(link, jiffies + 2 * HZ,
					  ahci_check_ready);
		if (rc)
			ahci_kick_engine(ap);
	}
	return rc;
}