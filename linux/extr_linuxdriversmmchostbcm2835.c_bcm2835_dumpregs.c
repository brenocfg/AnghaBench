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
struct mmc_request {int /*<<< orphan*/  stop; TYPE_2__* data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  sbc; } ;
struct device {int dummy; } ;
struct bcm2835_host {scalar_t__ ioaddr; TYPE_1__* pdev; struct mmc_request* mrq; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; int /*<<< orphan*/  blksz; int /*<<< orphan*/  blocks; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ SDARG ; 
 scalar_t__ SDCDIV ; 
 scalar_t__ SDCMD ; 
 scalar_t__ SDEDM ; 
 scalar_t__ SDHBCT ; 
 scalar_t__ SDHBLC ; 
 scalar_t__ SDHCFG ; 
 scalar_t__ SDHSTS ; 
 scalar_t__ SDRSP0 ; 
 scalar_t__ SDRSP1 ; 
 scalar_t__ SDRSP2 ; 
 scalar_t__ SDRSP3 ; 
 scalar_t__ SDTOUT ; 
 scalar_t__ SDVDD ; 
 int /*<<< orphan*/  bcm2835_dumpcmd (struct bcm2835_host*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void bcm2835_dumpregs(struct bcm2835_host *host)
{
	struct mmc_request *mrq = host->mrq;
	struct device *dev = &host->pdev->dev;

	if (mrq) {
		bcm2835_dumpcmd(host, mrq->sbc, "sbc");
		bcm2835_dumpcmd(host, mrq->cmd, "cmd");
		if (mrq->data) {
			dev_dbg(dev, "data blocks %x blksz %x - err %d\n",
				mrq->data->blocks,
				mrq->data->blksz,
				mrq->data->error);
		}
		bcm2835_dumpcmd(host, mrq->stop, "stop");
	}

	dev_dbg(dev, "=========== REGISTER DUMP ===========\n");
	dev_dbg(dev, "SDCMD  0x%08x\n", readl(host->ioaddr + SDCMD));
	dev_dbg(dev, "SDARG  0x%08x\n", readl(host->ioaddr + SDARG));
	dev_dbg(dev, "SDTOUT 0x%08x\n", readl(host->ioaddr + SDTOUT));
	dev_dbg(dev, "SDCDIV 0x%08x\n", readl(host->ioaddr + SDCDIV));
	dev_dbg(dev, "SDRSP0 0x%08x\n", readl(host->ioaddr + SDRSP0));
	dev_dbg(dev, "SDRSP1 0x%08x\n", readl(host->ioaddr + SDRSP1));
	dev_dbg(dev, "SDRSP2 0x%08x\n", readl(host->ioaddr + SDRSP2));
	dev_dbg(dev, "SDRSP3 0x%08x\n", readl(host->ioaddr + SDRSP3));
	dev_dbg(dev, "SDHSTS 0x%08x\n", readl(host->ioaddr + SDHSTS));
	dev_dbg(dev, "SDVDD  0x%08x\n", readl(host->ioaddr + SDVDD));
	dev_dbg(dev, "SDEDM  0x%08x\n", readl(host->ioaddr + SDEDM));
	dev_dbg(dev, "SDHCFG 0x%08x\n", readl(host->ioaddr + SDHCFG));
	dev_dbg(dev, "SDHBCT 0x%08x\n", readl(host->ioaddr + SDHBCT));
	dev_dbg(dev, "SDHBLC 0x%08x\n", readl(host->ioaddr + SDHBLC));
	dev_dbg(dev, "===========================================\n");
}