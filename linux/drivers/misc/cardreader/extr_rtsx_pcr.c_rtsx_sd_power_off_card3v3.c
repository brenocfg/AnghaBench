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
 int /*<<< orphan*/  CARD_CLK_EN ; 
 int /*<<< orphan*/  CARD_OE ; 
 int MS_CLK_EN ; 
 int /*<<< orphan*/  RTSX_SD_CARD ; 
 int SD40_CLK_EN ; 
 int SD_CLK_EN ; 
 int SD_OUTPUT_EN ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtsx_pci_card_power_off (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_card_pull_ctl_disable (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int rtsx_sd_power_off_card3v3(struct rtsx_pcr *pcr)
{
	rtsx_pci_write_register(pcr, CARD_CLK_EN, SD_CLK_EN |
		MS_CLK_EN | SD40_CLK_EN, 0);
	rtsx_pci_write_register(pcr, CARD_OE, SD_OUTPUT_EN, 0);
	rtsx_pci_card_power_off(pcr, RTSX_SD_CARD);

	msleep(50);

	rtsx_pci_card_pull_ctl_disable(pcr, RTSX_SD_CARD);

	return 0;
}