#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ide_port_ops {int /*<<< orphan*/  (* cable_detect ) (TYPE_1__*) ;} ;
struct TYPE_4__ {int ultra_mask; int /*<<< orphan*/  cbl; struct ide_port_ops* port_ops; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA40_SHORT ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void ide_port_cable_detect(ide_hwif_t *hwif)
{
	const struct ide_port_ops *port_ops = hwif->port_ops;

	if (port_ops && port_ops->cable_detect && (hwif->ultra_mask & 0x78)) {
		if (hwif->cbl != ATA_CBL_PATA40_SHORT)
			hwif->cbl = port_ops->cable_detect(hwif);
	}
}