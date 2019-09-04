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
struct piix_host_priv {scalar_t__* map; int /*<<< orphan*/  sidpr; } ;
struct pci_dev {int dummy; } ;
struct ata_link {int dummy; } ;
struct ata_port {int flags; int /*<<< orphan*/ * ops; struct ata_link link; } ;
struct ata_host {struct ata_port** ports; int /*<<< orphan*/  dev; struct piix_host_priv* private_data; } ;

/* Variables and functions */
 int ATA_FLAG_SLAVE_POSS ; 
 int /*<<< orphan*/  DRV_NAME ; 
 scalar_t__ IDE ; 
 int PIIX_FLAG_SIDPR ; 
 int PIIX_SIDPR_BAR ; 
 scalar_t__ PIIX_SIDPR_LEN ; 
 int /*<<< orphan*/  SCR_CONTROL ; 
 int ata_slave_link_init (struct ata_port*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int) ; 
 scalar_t__ pcim_iomap_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 
 scalar_t__ piix_no_sidpr (struct ata_host*) ; 
 int /*<<< orphan*/  piix_sidpr_sata_ops ; 
 int /*<<< orphan*/  piix_sidpr_scr_read (struct ata_link*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  piix_sidpr_scr_write (struct ata_link*,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int piix_init_sidpr(struct ata_host *host)
{
	struct pci_dev *pdev = to_pci_dev(host->dev);
	struct piix_host_priv *hpriv = host->private_data;
	struct ata_link *link0 = &host->ports[0]->link;
	u32 scontrol;
	int i, rc;

	/* check for availability */
	for (i = 0; i < 4; i++)
		if (hpriv->map[i] == IDE)
			return 0;

	/* is it blacklisted? */
	if (piix_no_sidpr(host))
		return 0;

	if (!(host->ports[0]->flags & PIIX_FLAG_SIDPR))
		return 0;

	if (pci_resource_start(pdev, PIIX_SIDPR_BAR) == 0 ||
	    pci_resource_len(pdev, PIIX_SIDPR_BAR) != PIIX_SIDPR_LEN)
		return 0;

	if (pcim_iomap_regions(pdev, 1 << PIIX_SIDPR_BAR, DRV_NAME))
		return 0;

	hpriv->sidpr = pcim_iomap_table(pdev)[PIIX_SIDPR_BAR];

	/* SCR access via SIDPR doesn't work on some configurations.
	 * Give it a test drive by inhibiting power save modes which
	 * we'll do anyway.
	 */
	piix_sidpr_scr_read(link0, SCR_CONTROL, &scontrol);

	/* if IPM is already 3, SCR access is probably working.  Don't
	 * un-inhibit power save modes as BIOS might have inhibited
	 * them for a reason.
	 */
	if ((scontrol & 0xf00) != 0x300) {
		scontrol |= 0x300;
		piix_sidpr_scr_write(link0, SCR_CONTROL, scontrol);
		piix_sidpr_scr_read(link0, SCR_CONTROL, &scontrol);

		if ((scontrol & 0xf00) != 0x300) {
			dev_info(host->dev,
				 "SCR access via SIDPR is available but doesn't work\n");
			return 0;
		}
	}

	/* okay, SCRs available, set ops and ask libata for slave_link */
	for (i = 0; i < 2; i++) {
		struct ata_port *ap = host->ports[i];

		ap->ops = &piix_sidpr_sata_ops;

		if (ap->flags & ATA_FLAG_SLAVE_POSS) {
			rc = ata_slave_link_init(ap);
			if (rc)
				return rc;
		}
	}

	return 0;
}