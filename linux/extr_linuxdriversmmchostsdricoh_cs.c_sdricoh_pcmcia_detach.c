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
struct sdricoh_host {int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  iobase; } ;
struct pcmcia_device {int /*<<< orphan*/  dev; struct mmc_host* priv; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct sdricoh_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void sdricoh_pcmcia_detach(struct pcmcia_device *link)
{
	struct mmc_host *mmc = link->priv;

	dev_dbg(&link->dev, "detach\n");

	/* remove mmc host */
	if (mmc) {
		struct sdricoh_host *host = mmc_priv(mmc);
		mmc_remove_host(mmc);
		pci_iounmap(host->pci_dev, host->iobase);
		pci_dev_put(host->pci_dev);
		mmc_free_host(mmc);
	}
	pcmcia_disable_device(link);

}