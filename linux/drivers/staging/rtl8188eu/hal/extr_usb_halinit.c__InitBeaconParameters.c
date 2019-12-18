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
struct hal_data_8188e {void* RegCR_1; void* RegReg542; void* RegFwHwTxQCtrl; void* RegTxPause; void* RegBcnCtrlVal; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCN_DMA_ATIME_INT_TIME ; 
 int /*<<< orphan*/  DRIVER_EARLY_INT_TIME ; 
 int /*<<< orphan*/  REG_BCNDMATIM ; 
 scalar_t__ REG_BCNTCFG ; 
 scalar_t__ REG_BCN_CTRL ; 
 scalar_t__ REG_CR ; 
 int /*<<< orphan*/  REG_DRVERLYINT ; 
 scalar_t__ REG_FWHW_TXQ_CTRL ; 
 scalar_t__ REG_TBTT_PROHIBIT ; 
 scalar_t__ REG_TXPAUSE ; 
 void* usb_read8 (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  usb_write16 (struct adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _InitBeaconParameters(struct adapter *Adapter)
{
	struct hal_data_8188e *haldata = Adapter->HalData;

	usb_write16(Adapter, REG_BCN_CTRL, 0x1010);

	/*  TODO: Remove these magic number */
	usb_write16(Adapter, REG_TBTT_PROHIBIT, 0x6404);/*  ms */
	usb_write8(Adapter, REG_DRVERLYINT, DRIVER_EARLY_INT_TIME);/*  5ms */
	usb_write8(Adapter, REG_BCNDMATIM, BCN_DMA_ATIME_INT_TIME); /*  2ms */

	/*  Suggested by designer timchen. Change beacon AIFS to the largest number */
	/*  beacause test chip does not contension before sending beacon. by tynli. 2009.11.03 */
	usb_write16(Adapter, REG_BCNTCFG, 0x660F);

	haldata->RegBcnCtrlVal = usb_read8(Adapter, REG_BCN_CTRL);
	haldata->RegTxPause = usb_read8(Adapter, REG_TXPAUSE);
	haldata->RegFwHwTxQCtrl = usb_read8(Adapter, REG_FWHW_TXQ_CTRL + 2);
	haldata->RegReg542 = usb_read8(Adapter, REG_TBTT_PROHIBIT + 2);
	haldata->RegCR_1 = usb_read8(Adapter, REG_CR + 1);
}