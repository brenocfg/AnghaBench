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
struct ata_port {int print_id; scalar_t__ cbl; } ;
struct TYPE_2__ {scalar_t__ cbl; int /*<<< orphan*/  name; } ;
struct ata_force_ent {int port; TYPE_1__ param; } ;

/* Variables and functions */
 scalar_t__ ATA_CBL_NONE ; 
 struct ata_force_ent* ata_force_tbl ; 
 int ata_force_tbl_size ; 
 int /*<<< orphan*/  ata_port_notice (struct ata_port*,char*,int /*<<< orphan*/ ) ; 

void ata_force_cbl(struct ata_port *ap)
{
	int i;

	for (i = ata_force_tbl_size - 1; i >= 0; i--) {
		const struct ata_force_ent *fe = &ata_force_tbl[i];

		if (fe->port != -1 && fe->port != ap->print_id)
			continue;

		if (fe->param.cbl == ATA_CBL_NONE)
			continue;

		ap->cbl = fe->param.cbl;
		ata_port_notice(ap, "FORCE: cable set to %s\n", fe->param.name);
		return;
	}
}