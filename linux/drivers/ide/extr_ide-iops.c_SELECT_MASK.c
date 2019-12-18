#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ide_port_ops {int /*<<< orphan*/  (* maskproc ) (TYPE_2__*,int) ;} ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {struct ide_port_ops* port_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

void SELECT_MASK(ide_drive_t *drive, int mask)
{
	const struct ide_port_ops *port_ops = drive->hwif->port_ops;

	if (port_ops && port_ops->maskproc)
		port_ops->maskproc(drive, mask);
}