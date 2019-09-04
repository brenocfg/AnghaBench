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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int BPP_POWER_5_PERCENT_ON ; 
 int BPP_POWER_MASK ; 
 int BPP_POWER_OFF ; 
 unsigned int CARD_EXIST ; 
 int /*<<< orphan*/  CARD_PWR_CTL ; 
 int CD_DISABLE_MASK ; 
 int CD_ENABLE ; 
 int /*<<< orphan*/  CD_PAD_CTL ; 
 int /*<<< orphan*/  EFUSE_CONTENT ; 
 int MS_CD_EN_ONLY ; 
 unsigned int MS_EXIST ; 
 int /*<<< orphan*/  RTSX_BIPR ; 
 int SD_CD_EN_ONLY ; 
 unsigned int SD_EXIST ; 
 int hweight32 (unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pcr_dbg (struct rtsx_pcr*,char*,unsigned int) ; 
 unsigned int rtsx_pci_readl (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static unsigned int rtl8411_cd_deglitch(struct rtsx_pcr *pcr)
{
	unsigned int card_exist;

	card_exist = rtsx_pci_readl(pcr, RTSX_BIPR);
	card_exist &= CARD_EXIST;
	if (!card_exist) {
		/* Enable card CD */
		rtsx_pci_write_register(pcr, CD_PAD_CTL,
				CD_DISABLE_MASK, CD_ENABLE);
		/* Enable card interrupt */
		rtsx_pci_write_register(pcr, EFUSE_CONTENT, 0xe0, 0x00);
		return 0;
	}

	if (hweight32(card_exist) > 1) {
		rtsx_pci_write_register(pcr, CARD_PWR_CTL,
				BPP_POWER_MASK, BPP_POWER_5_PERCENT_ON);
		msleep(100);

		card_exist = rtsx_pci_readl(pcr, RTSX_BIPR);
		if (card_exist & MS_EXIST)
			card_exist = MS_EXIST;
		else if (card_exist & SD_EXIST)
			card_exist = SD_EXIST;
		else
			card_exist = 0;

		rtsx_pci_write_register(pcr, CARD_PWR_CTL,
				BPP_POWER_MASK, BPP_POWER_OFF);

		pcr_dbg(pcr, "After CD deglitch, card_exist = 0x%x\n",
			card_exist);
	}

	if (card_exist & MS_EXIST) {
		/* Disable SD interrupt */
		rtsx_pci_write_register(pcr, EFUSE_CONTENT, 0xe0, 0x40);
		rtsx_pci_write_register(pcr, CD_PAD_CTL,
				CD_DISABLE_MASK, MS_CD_EN_ONLY);
	} else if (card_exist & SD_EXIST) {
		/* Disable MS interrupt */
		rtsx_pci_write_register(pcr, EFUSE_CONTENT, 0xe0, 0x80);
		rtsx_pci_write_register(pcr, CD_PAD_CTL,
				CD_DISABLE_MASK, SD_CD_EN_ONLY);
	}

	return card_exist;
}