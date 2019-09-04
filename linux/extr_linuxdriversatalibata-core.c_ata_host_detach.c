#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ata_host {int n_ports; int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_acpi_dissociate (struct ata_host*) ; 
 int /*<<< orphan*/  ata_port_detach (int /*<<< orphan*/ ) ; 

void ata_host_detach(struct ata_host *host)
{
	int i;

	for (i = 0; i < host->n_ports; i++)
		ata_port_detach(host->ports[i]);

	/* the host is dead now, dissociate ACPI */
	ata_acpi_dissociate(host);
}