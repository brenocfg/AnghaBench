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
struct ata_port {int /*<<< orphan*/  pflags; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PFLAG_FROZEN ; 

int ata_sas_port_start(struct ata_port *ap)
{
	/*
	 * the port is marked as frozen at allocation time, but if we don't
	 * have new eh, we won't thaw it
	 */
	if (!ap->ops->error_handler)
		ap->pflags &= ~ATA_PFLAG_FROZEN;
	return 0;
}