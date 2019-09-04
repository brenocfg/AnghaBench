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
struct device {int dummy; } ;
struct ata_port {TYPE_1__* ops; } ;
struct ata_host {int flags; int n_ports; TYPE_2__* ops; struct ata_port** ports; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* host_stop ) (struct ata_host*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* port_stop ) (struct ata_port*) ;} ;

/* Variables and functions */
 int ATA_HOST_STARTED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ata_host* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 
 int /*<<< orphan*/  stub2 (struct ata_host*) ; 

__attribute__((used)) static void ata_host_stop(struct device *gendev, void *res)
{
	struct ata_host *host = dev_get_drvdata(gendev);
	int i;

	WARN_ON(!(host->flags & ATA_HOST_STARTED));

	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];

		if (ap->ops->port_stop)
			ap->ops->port_stop(ap);
	}

	if (host->ops->host_stop)
		host->ops->host_stop(host);
}