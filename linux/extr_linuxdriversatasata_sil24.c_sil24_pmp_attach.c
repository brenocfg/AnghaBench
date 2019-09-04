#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct ata_port {int /*<<< orphan*/  flags; TYPE_2__ link; } ;
struct TYPE_3__ {int /*<<< orphan*/ * gscr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_FLAG_NCQ ; 
 int /*<<< orphan*/  ata_port_info (struct ata_port*,char*) ; 
 int sata_pmp_gscr_devid (int /*<<< orphan*/ *) ; 
 int sata_pmp_gscr_vendor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sil24_config_pmp (struct ata_port*,int) ; 
 int /*<<< orphan*/  sil24_init_port (struct ata_port*) ; 

__attribute__((used)) static void sil24_pmp_attach(struct ata_port *ap)
{
	u32 *gscr = ap->link.device->gscr;

	sil24_config_pmp(ap, 1);
	sil24_init_port(ap);

	if (sata_pmp_gscr_vendor(gscr) == 0x11ab &&
	    sata_pmp_gscr_devid(gscr) == 0x4140) {
		ata_port_info(ap,
			"disabling NCQ support due to sil24-mv4140 quirk\n");
		ap->flags &= ~ATA_FLAG_NCQ;
	}
}