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
struct ata_port {int /*<<< orphan*/  tdev; } ;
struct ata_host {int n_ports; struct ata_port** ports; } ;
struct ata_acpi_gtm {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 struct ata_acpi_gtm* ata_acpi_init_gtm (struct ata_port*) ; 
 int /*<<< orphan*/  ata_acpi_stm (struct ata_port*,struct ata_acpi_gtm const*) ; 

void ata_acpi_dissociate(struct ata_host *host)
{
	int i;

	/* Restore initial _GTM values so that driver which attaches
	 * afterward can use them too.
	 */
	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];
		const struct ata_acpi_gtm *gtm = ata_acpi_init_gtm(ap);

		if (ACPI_HANDLE(&ap->tdev) && gtm)
			ata_acpi_stm(ap, gtm);
	}
}