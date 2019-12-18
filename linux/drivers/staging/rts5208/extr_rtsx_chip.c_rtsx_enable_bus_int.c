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
struct rtsx_chip {int max_lun; int* lun2card; scalar_t__ ic_version; int /*<<< orphan*/  adma_mode; scalar_t__ hw_bypass_sd; } ;

/* Variables and functions */
 int DATA_DONE_INT_EN ; 
 int DELINK_INT_EN ; 
 scalar_t__ IC_VER_C ; 
 int MS_CARD ; 
 int MS_INT_EN ; 
 int OC_INT_EN ; 
 int /*<<< orphan*/  RTSX_BIER ; 
 int SD_CARD ; 
 int SD_INT_EN ; 
 int TRANS_FAIL_INT_EN ; 
 int TRANS_OK_INT_EN ; 
 int XD_CARD ; 
 int XD_INT_EN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_writel (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 

void rtsx_enable_bus_int(struct rtsx_chip *chip)
{
	u32 reg = 0;
#ifndef DISABLE_CARD_INT
	int i;
#endif

	reg = TRANS_OK_INT_EN | TRANS_FAIL_INT_EN;

#ifndef DISABLE_CARD_INT
	for (i = 0; i <= chip->max_lun; i++) {
		dev_dbg(rtsx_dev(chip), "lun2card[%d] = 0x%02x\n",
			i, chip->lun2card[i]);

		if (chip->lun2card[i] & XD_CARD)
			reg |= XD_INT_EN;
		if (chip->lun2card[i] & SD_CARD)
			reg |= SD_INT_EN;
		if (chip->lun2card[i] & MS_CARD)
			reg |= MS_INT_EN;
	}
	if (chip->hw_bypass_sd)
		reg &= ~((u32)SD_INT_EN);
#endif

	if (chip->ic_version >= IC_VER_C)
		reg |= DELINK_INT_EN;
#ifdef SUPPORT_OCP
	reg |= OC_INT_EN;
#endif
	if (!chip->adma_mode)
		reg |= DATA_DONE_INT_EN;

	/* Enable Bus Interrupt */
	rtsx_writel(chip, RTSX_BIER, reg);

	dev_dbg(rtsx_dev(chip), "RTSX_BIER: 0x%08x\n", reg);
}