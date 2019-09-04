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
typedef  int u8 ;
typedef  int u32 ;
struct ata_host {unsigned int n_ports; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ports; int /*<<< orphan*/  dev; scalar_t__* iomap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 size_t VSC_MMIO_BAR ; 
 scalar_t__ VSC_SATA_INT_STAT_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vsc_port_intr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t vsc_sata_interrupt(int irq, void *dev_instance)
{
	struct ata_host *host = dev_instance;
	unsigned int i;
	unsigned int handled = 0;
	u32 status;

	status = readl(host->iomap[VSC_MMIO_BAR] + VSC_SATA_INT_STAT_OFFSET);

	if (unlikely(status == 0xffffffff || status == 0)) {
		if (status)
			dev_err(host->dev,
				": IRQ status == 0xffffffff, PCI fault or device removal?\n");
		goto out;
	}

	spin_lock(&host->lock);

	for (i = 0; i < host->n_ports; i++) {
		u8 port_status = (status >> (8 * i)) & 0xff;
		if (port_status) {
			vsc_port_intr(port_status, host->ports[i]);
			handled++;
		}
	}

	spin_unlock(&host->lock);
out:
	return IRQ_RETVAL(handled);
}