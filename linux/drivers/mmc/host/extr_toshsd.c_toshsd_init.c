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
typedef  int /*<<< orphan*/  u32 ;
struct toshsd_host {scalar_t__ ioaddr; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ SDIO_BASE ; 
 scalar_t__ SDIO_CLOCKNWAITCTRL ; 
 int SD_BUF_CMD_TIMEOUT ; 
 int SD_BUF_READ_ENABLE ; 
 int SD_BUF_WRITE_ENABLE ; 
 scalar_t__ SD_CARDCLOCKCTRL ; 
 scalar_t__ SD_CARDSTATUS ; 
 int SD_CARD_CARD_INSERTED_0 ; 
 int SD_CARD_CARD_REMOVED_0 ; 
 int SD_CARD_RESP_END ; 
 int SD_CARD_RW_END ; 
 scalar_t__ SD_ERRORSTATUS0 ; 
 scalar_t__ SD_INTMASKCARD ; 
 int /*<<< orphan*/  SD_PCICFG_CARDDETECT ; 
 int /*<<< orphan*/  SD_PCICFG_CLKSTOP ; 
 int SD_PCICFG_CLKSTOP_ENABLE_ALL ; 
 int SD_PCICFG_LED_ENABLE1_START ; 
 int SD_PCICFG_LED_ENABLE2_START ; 
 int /*<<< orphan*/  SD_PCICFG_SDLED_ENABLE1 ; 
 int /*<<< orphan*/  SD_PCICFG_SDLED_ENABLE2 ; 
 scalar_t__ SD_SOFTWARERESET ; 
 scalar_t__ SD_STOPINTERNAL ; 
 scalar_t__ SD_TRANSACTIONCTRL ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void toshsd_init(struct toshsd_host *host)
{
	/* enable clock */
	pci_write_config_byte(host->pdev, SD_PCICFG_CLKSTOP,
					SD_PCICFG_CLKSTOP_ENABLE_ALL);
	pci_write_config_byte(host->pdev, SD_PCICFG_CARDDETECT, 2);

	/* reset */
	iowrite16(0, host->ioaddr + SD_SOFTWARERESET); /* assert */
	mdelay(2);
	iowrite16(1, host->ioaddr + SD_SOFTWARERESET); /* deassert */
	mdelay(2);

	/* Clear card registers */
	iowrite16(0, host->ioaddr + SD_CARDCLOCKCTRL);
	iowrite32(0, host->ioaddr + SD_CARDSTATUS);
	iowrite32(0, host->ioaddr + SD_ERRORSTATUS0);
	iowrite16(0, host->ioaddr + SD_STOPINTERNAL);

	/* SDIO clock? */
	iowrite16(0x100, host->ioaddr + SDIO_BASE + SDIO_CLOCKNWAITCTRL);

	/* enable LED */
	pci_write_config_byte(host->pdev, SD_PCICFG_SDLED_ENABLE1,
					SD_PCICFG_LED_ENABLE1_START);
	pci_write_config_byte(host->pdev, SD_PCICFG_SDLED_ENABLE2,
					SD_PCICFG_LED_ENABLE2_START);

	/* set interrupt masks */
	iowrite32(~(u32)(SD_CARD_RESP_END | SD_CARD_RW_END
			| SD_CARD_CARD_REMOVED_0 | SD_CARD_CARD_INSERTED_0
			| SD_BUF_READ_ENABLE | SD_BUF_WRITE_ENABLE
			| SD_BUF_CMD_TIMEOUT),
			host->ioaddr + SD_INTMASKCARD);

	iowrite16(0x1000, host->ioaddr + SD_TRANSACTIONCTRL);
}