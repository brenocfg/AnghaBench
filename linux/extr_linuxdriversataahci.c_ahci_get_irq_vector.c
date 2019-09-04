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
struct ata_host {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahci_get_irq_vector(struct ata_host *host, int port)
{
	return pci_irq_vector(to_pci_dev(host->dev), port);
}