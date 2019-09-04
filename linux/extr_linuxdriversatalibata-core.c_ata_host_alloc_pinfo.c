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
struct device {int dummy; } ;
struct ata_port_info {int /*<<< orphan*/ * port_ops; int /*<<< orphan*/  link_flags; int /*<<< orphan*/  flags; int /*<<< orphan*/  udma_mask; int /*<<< orphan*/  mwdma_mask; int /*<<< orphan*/  pio_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ata_port {int /*<<< orphan*/ * ops; TYPE_1__ link; int /*<<< orphan*/  flags; int /*<<< orphan*/  udma_mask; int /*<<< orphan*/  mwdma_mask; int /*<<< orphan*/  pio_mask; } ;
struct ata_host {int n_ports; int /*<<< orphan*/ * ops; struct ata_port** ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_dummy_port_ops ; 
 struct ata_host* ata_host_alloc (struct device*,int) ; 

struct ata_host *ata_host_alloc_pinfo(struct device *dev,
				      const struct ata_port_info * const * ppi,
				      int n_ports)
{
	const struct ata_port_info *pi;
	struct ata_host *host;
	int i, j;

	host = ata_host_alloc(dev, n_ports);
	if (!host)
		return NULL;

	for (i = 0, j = 0, pi = NULL; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];

		if (ppi[j])
			pi = ppi[j++];

		ap->pio_mask = pi->pio_mask;
		ap->mwdma_mask = pi->mwdma_mask;
		ap->udma_mask = pi->udma_mask;
		ap->flags |= pi->flags;
		ap->link.flags |= pi->link_flags;
		ap->ops = pi->port_ops;

		if (!host->ops && (pi->port_ops != &ata_dummy_port_ops))
			host->ops = pi->port_ops;
	}

	return host;
}