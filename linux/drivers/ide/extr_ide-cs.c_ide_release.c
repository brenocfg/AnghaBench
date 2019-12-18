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
struct pcmcia_device {int /*<<< orphan*/  dev; TYPE_2__* priv; } ;
struct ide_host {TYPE_3__** ports; } ;
struct TYPE_5__ {scalar_t__ ndev; struct ide_host* host; } ;
typedef  TYPE_2__ ide_info_t ;
struct TYPE_4__ {unsigned long data_addr; unsigned long ctl_addr; } ;
struct TYPE_6__ {TYPE_1__ io_ports; } ;
typedef  TYPE_3__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  ide_host_remove (struct ide_host*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  release_region (unsigned long,int) ; 

__attribute__((used)) static void ide_release(struct pcmcia_device *link)
{
    ide_info_t *info = link->priv;
    struct ide_host *host = info->host;

    dev_dbg(&link->dev, "ide_release(0x%p)\n", link);

    if (info->ndev) {
	ide_hwif_t *hwif = host->ports[0];
	unsigned long data_addr, ctl_addr;

	data_addr = hwif->io_ports.data_addr;
	ctl_addr = hwif->io_ports.ctl_addr;

	ide_host_remove(host);
	info->ndev = 0;

	release_region(ctl_addr, 1);
	release_region(data_addr, 8);
    }

    pcmcia_disable_device(link);
}