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
typedef  int u32 ;
struct bcm2835_host {int hcfg; scalar_t__ sectors; scalar_t__ clock; int /*<<< orphan*/  mmc; scalar_t__ debug; } ;

/* Variables and functions */
 int FIFO_READ_THRESHOLD ; 
 int FIFO_WRITE_THRESHOLD ; 
 int /*<<< orphan*/  SDARG ; 
 int /*<<< orphan*/  SDCDIV ; 
 int SDCDIV_MAX_CDIV ; 
 int /*<<< orphan*/  SDCMD ; 
 int /*<<< orphan*/  SDEDM ; 
 int SDEDM_READ_THRESHOLD_SHIFT ; 
 int SDEDM_THRESHOLD_MASK ; 
 int SDEDM_WRITE_THRESHOLD_SHIFT ; 
 int /*<<< orphan*/  SDHBCT ; 
 int /*<<< orphan*/  SDHBLC ; 
 int /*<<< orphan*/  SDHCFG ; 
 int /*<<< orphan*/  SDHSTS ; 
 int /*<<< orphan*/  SDTOUT ; 
 int bcm2835_sdhost_read (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_sdhost_set_power (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  bcm2835_sdhost_write (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_sdhost_reset_internal(struct bcm2835_host *host)
{
	u32 temp;

	if (host->debug)
		pr_info("%s: reset\n", mmc_hostname(host->mmc));

	bcm2835_sdhost_set_power(host, false);

	bcm2835_sdhost_write(host, 0, SDCMD);
	bcm2835_sdhost_write(host, 0, SDARG);
	bcm2835_sdhost_write(host, 0xf00000, SDTOUT);
	bcm2835_sdhost_write(host, 0, SDCDIV);
	bcm2835_sdhost_write(host, 0x7f8, SDHSTS); /* Write 1s to clear */
	bcm2835_sdhost_write(host, 0, SDHCFG);
	bcm2835_sdhost_write(host, 0, SDHBCT);
	bcm2835_sdhost_write(host, 0, SDHBLC);

	/* Limit fifo usage due to silicon bug */
	temp = bcm2835_sdhost_read(host, SDEDM);
	temp &= ~((SDEDM_THRESHOLD_MASK<<SDEDM_READ_THRESHOLD_SHIFT) |
		  (SDEDM_THRESHOLD_MASK<<SDEDM_WRITE_THRESHOLD_SHIFT));
	temp |= (FIFO_READ_THRESHOLD << SDEDM_READ_THRESHOLD_SHIFT) |
		(FIFO_WRITE_THRESHOLD << SDEDM_WRITE_THRESHOLD_SHIFT);
	bcm2835_sdhost_write(host, temp, SDEDM);
	mdelay(10);
	bcm2835_sdhost_set_power(host, true);
	mdelay(10);
	host->clock = 0;
	host->sectors = 0;
	bcm2835_sdhost_write(host, host->hcfg, SDHCFG);
	bcm2835_sdhost_write(host, SDCDIV_MAX_CDIV, SDCDIV);
	mmiowb();
}