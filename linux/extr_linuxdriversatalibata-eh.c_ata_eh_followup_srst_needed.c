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
struct ata_link {int flags; int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int ATA_LFLAG_NO_SRST ; 
 int EAGAIN ; 
 scalar_t__ ata_is_host_link (struct ata_link*) ; 
 scalar_t__ ata_link_offline (struct ata_link*) ; 
 scalar_t__ sata_pmp_supported (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ata_eh_followup_srst_needed(struct ata_link *link, int rc)
{
	if ((link->flags & ATA_LFLAG_NO_SRST) || ata_link_offline(link))
		return 0;
	if (rc == -EAGAIN)
		return 1;
	if (sata_pmp_supported(link->ap) && ata_is_host_link(link))
		return 1;
	return 0;
}