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
struct ata_host {int /*<<< orphan*/ * ports; scalar_t__* iomap; } ;

/* Variables and functions */
 size_t ADMA_MMIO_BAR ; 
 scalar_t__ ADMA_MODE_LOCK ; 
 unsigned int ADMA_PORTS ; 
 int /*<<< orphan*/  adma_reset_engine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void adma_host_init(struct ata_host *host, unsigned int chip_id)
{
	unsigned int port_no;

	/* enable/lock aGO operation */
	writeb(7, host->iomap[ADMA_MMIO_BAR] + ADMA_MODE_LOCK);

	/* reset the ADMA logic */
	for (port_no = 0; port_no < ADMA_PORTS; ++port_no)
		adma_reset_engine(host->ports[port_no]);
}