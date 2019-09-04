#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int horkage_on; int horkage_off; int /*<<< orphan*/  name; } ;
struct ata_force_ent {int port; int device; TYPE_2__ param; } ;
struct ata_device {int devno; int horkage; TYPE_3__* link; } ;
struct TYPE_6__ {int pmp; TYPE_1__* ap; } ;
struct TYPE_4__ {int print_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_dev_notice (struct ata_device*,char*,int /*<<< orphan*/ ) ; 
 struct ata_force_ent* ata_force_tbl ; 
 int ata_force_tbl_size ; 
 scalar_t__ ata_is_host_link (TYPE_3__*) ; 

__attribute__((used)) static void ata_force_horkage(struct ata_device *dev)
{
	int devno = dev->link->pmp + dev->devno;
	int alt_devno = devno;
	int i;

	/* allow n.15/16 for devices attached to host port */
	if (ata_is_host_link(dev->link))
		alt_devno += 15;

	for (i = 0; i < ata_force_tbl_size; i++) {
		const struct ata_force_ent *fe = &ata_force_tbl[i];

		if (fe->port != -1 && fe->port != dev->link->ap->print_id)
			continue;

		if (fe->device != -1 && fe->device != devno &&
		    fe->device != alt_devno)
			continue;

		if (!(~dev->horkage & fe->param.horkage_on) &&
		    !(dev->horkage & fe->param.horkage_off))
			continue;

		dev->horkage |= fe->param.horkage_on;
		dev->horkage &= ~fe->param.horkage_off;

		ata_dev_notice(dev, "FORCE: horkage modified (%s)\n",
			       fe->param.name);
	}
}