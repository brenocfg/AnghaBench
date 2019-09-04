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
struct ata_port {int dummy; } ;
struct ata_link {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_WAIT_AFTER_RESET ; 
 int /*<<< orphan*/  ata_msleep (struct ata_port*,int /*<<< orphan*/ ) ; 
 int ata_sff_wait_ready (struct ata_link*,unsigned long) ; 

__attribute__((used)) static int sata_rcar_wait_after_reset(struct ata_link *link,
				      unsigned long deadline)
{
	struct ata_port *ap = link->ap;

	ata_msleep(ap, ATA_WAIT_AFTER_RESET);

	return ata_sff_wait_ready(link, deadline);
}