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
typedef  int u16 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT_CHECK_SUM_OK ; 
 int BIT_FW_DW_RDY ; 
 int BIT_MCUFWDL_EN ; 
 int /*<<< orphan*/  BTI_PAGE_OVF ; 
 int /*<<< orphan*/  REG_MCUFW_CTRL ; 
 int /*<<< orphan*/  REG_TXDMA_STATUS ; 
 int rtw_read16 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void download_firmware_end_flow(struct rtw_dev *rtwdev)
{
	u16 fw_ctrl;

	rtw_write32(rtwdev, REG_TXDMA_STATUS, BTI_PAGE_OVF);

	/* Check IMEM & DMEM checksum is OK or not */
	fw_ctrl = rtw_read16(rtwdev, REG_MCUFW_CTRL);
	if ((fw_ctrl & BIT_CHECK_SUM_OK) != BIT_CHECK_SUM_OK)
		return;

	fw_ctrl = (fw_ctrl | BIT_FW_DW_RDY) & ~BIT_MCUFWDL_EN;
	rtw_write16(rtwdev, REG_MCUFW_CTRL, fw_ctrl);
}