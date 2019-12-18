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
struct HAL_VERSION {int CUTVersion; int /*<<< orphan*/  VendorType; int /*<<< orphan*/  ChipType; } ;
struct hal_data_8188e {struct HAL_VERSION VersionID; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_VENDOR_TSMC ; 
 int /*<<< orphan*/  CHIP_VENDOR_UMC ; 
 int CHIP_VER_RTL_MASK ; 
 int CHIP_VER_RTL_SHIFT ; 
 int /*<<< orphan*/  NORMAL_CHIP ; 
 int /*<<< orphan*/  REG_SYS_CFG ; 
 int RTL_ID ; 
 int /*<<< orphan*/  TEST_CHIP ; 
 int VENDOR_ID ; 
 int /*<<< orphan*/  dump_chip_info (struct HAL_VERSION) ; 
 int usb_read32 (struct adapter*,int /*<<< orphan*/ ) ; 

void rtw_hal_read_chip_version(struct adapter *padapter)
{
	u32				value32;
	struct HAL_VERSION		ChipVersion;
	struct hal_data_8188e *pHalData = padapter->HalData;

	value32 = usb_read32(padapter, REG_SYS_CFG);
	ChipVersion.ChipType = ((value32 & RTL_ID) ? TEST_CHIP : NORMAL_CHIP);
	ChipVersion.VendorType = ((value32 & VENDOR_ID) ? CHIP_VENDOR_UMC : CHIP_VENDOR_TSMC);
	ChipVersion.CUTVersion = (value32 & CHIP_VER_RTL_MASK)>>CHIP_VER_RTL_SHIFT; /*  IC version (CUT) */

	dump_chip_info(ChipVersion);

	pHalData->VersionID = ChipVersion;
}