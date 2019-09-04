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
struct bcm2835_host {int /*<<< orphan*/  mmc; TYPE_2__* mrq; } ;
struct TYPE_4__ {int /*<<< orphan*/  stop; TYPE_1__* data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  sbc; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; int /*<<< orphan*/  blksz; int /*<<< orphan*/  blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDARG ; 
 int /*<<< orphan*/  SDCDIV ; 
 int /*<<< orphan*/  SDCMD ; 
 int /*<<< orphan*/  SDEDM ; 
 int /*<<< orphan*/  SDHBCT ; 
 int /*<<< orphan*/  SDHBLC ; 
 int /*<<< orphan*/  SDHCFG ; 
 int /*<<< orphan*/  SDHSTS ; 
 int /*<<< orphan*/  SDRSP0 ; 
 int /*<<< orphan*/  SDRSP1 ; 
 int /*<<< orphan*/  SDRSP2 ; 
 int /*<<< orphan*/  SDRSP3 ; 
 int /*<<< orphan*/  SDTOUT ; 
 int /*<<< orphan*/  SDVDD ; 
 int /*<<< orphan*/  bcm2835_sdhost_dumpcmd (struct bcm2835_host*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_read (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void bcm2835_sdhost_dumpregs(struct bcm2835_host *host)
{
	if (host->mrq)
	{
		bcm2835_sdhost_dumpcmd(host, host->mrq->sbc, "sbc");
		bcm2835_sdhost_dumpcmd(host, host->mrq->cmd, "cmd");
		if (host->mrq->data)
			pr_info("%s: data blocks %x blksz %x - err %d\n",
			       mmc_hostname(host->mmc),
			       host->mrq->data->blocks,
			       host->mrq->data->blksz,
			       host->mrq->data->error);
		bcm2835_sdhost_dumpcmd(host, host->mrq->stop, "stop");
	}

	pr_info("%s: =========== REGISTER DUMP ===========\n",
		mmc_hostname(host->mmc));

	pr_info("%s: SDCMD  0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDCMD));
	pr_info("%s: SDARG  0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDARG));
	pr_info("%s: SDTOUT 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDTOUT));
	pr_info("%s: SDCDIV 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDCDIV));
	pr_info("%s: SDRSP0 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDRSP0));
	pr_info("%s: SDRSP1 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDRSP1));
	pr_info("%s: SDRSP2 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDRSP2));
	pr_info("%s: SDRSP3 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDRSP3));
	pr_info("%s: SDHSTS 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDHSTS));
	pr_info("%s: SDVDD  0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDVDD));
	pr_info("%s: SDEDM  0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDEDM));
	pr_info("%s: SDHCFG 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDHCFG));
	pr_info("%s: SDHBCT 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDHBCT));
	pr_info("%s: SDHBLC 0x%08x\n",
		mmc_hostname(host->mmc),
		bcm2835_sdhost_read(host, SDHBLC));

	pr_info("%s: ===========================================\n",
		mmc_hostname(host->mmc));
}