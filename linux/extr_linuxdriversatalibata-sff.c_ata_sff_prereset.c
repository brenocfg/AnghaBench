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
struct TYPE_2__ {int action; } ;
struct ata_eh_context {TYPE_1__ i; } ;
struct ata_link {struct ata_eh_context eh_context; } ;

/* Variables and functions */
 int ATA_EH_HARDRESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  ata_link_offline (struct ata_link*) ; 
 int /*<<< orphan*/  ata_link_warn (struct ata_link*,char*,int) ; 
 int ata_sff_wait_ready (struct ata_link*,unsigned long) ; 
 int ata_std_prereset (struct ata_link*,unsigned long) ; 

int ata_sff_prereset(struct ata_link *link, unsigned long deadline)
{
	struct ata_eh_context *ehc = &link->eh_context;
	int rc;

	rc = ata_std_prereset(link, deadline);
	if (rc)
		return rc;

	/* if we're about to do hardreset, nothing more to do */
	if (ehc->i.action & ATA_EH_HARDRESET)
		return 0;

	/* wait for !BSY if we don't know that no device is attached */
	if (!ata_link_offline(link)) {
		rc = ata_sff_wait_ready(link, deadline);
		if (rc && rc != -ENODEV) {
			ata_link_warn(link,
				      "device not ready (errno=%d), forcing hardreset\n",
				      rc);
			ehc->i.action |= ATA_EH_HARDRESET;
		}
	}

	return 0;
}