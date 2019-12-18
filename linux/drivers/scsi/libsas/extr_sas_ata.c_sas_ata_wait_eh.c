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
struct TYPE_2__ {struct ata_port* ap; } ;
struct domain_device {TYPE_1__ sata_dev; } ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_port_wait_eh (struct ata_port*) ; 
 int /*<<< orphan*/  dev_is_sata (struct domain_device*) ; 

void sas_ata_wait_eh(struct domain_device *dev)
{
	struct ata_port *ap;

	if (!dev_is_sata(dev))
		return;

	ap = dev->sata_dev.ap;
	ata_port_wait_eh(ap);
}