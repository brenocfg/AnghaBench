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
struct rtsx_pcr {int card_drive_sel; void* sd30_drive_sel_3v3; void* sd30_drive_sel_1v8; int /*<<< orphan*/  aspm_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCR_SETTING_REG1 ; 
 int /*<<< orphan*/  PCR_SETTING_REG2 ; 
 void* map_sd_drive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcr_dbg (struct rtsx_pcr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_read_config_dword (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtsx_reg_to_aspm (int /*<<< orphan*/ ) ; 
 int rtsx_reg_to_card_drive_sel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_reg_to_sd30_drive_sel_1v8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_reg_to_sd30_drive_sel_3v3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_vendor_setting_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rts5229_fetch_vendor_settings(struct rtsx_pcr *pcr)
{
	u32 reg;

	rtsx_pci_read_config_dword(pcr, PCR_SETTING_REG1, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG1, reg);

	if (!rtsx_vendor_setting_valid(reg))
		return;

	pcr->aspm_en = rtsx_reg_to_aspm(reg);
	pcr->sd30_drive_sel_1v8 =
		map_sd_drive(rtsx_reg_to_sd30_drive_sel_1v8(reg));
	pcr->card_drive_sel &= 0x3F;
	pcr->card_drive_sel |= rtsx_reg_to_card_drive_sel(reg);

	rtsx_pci_read_config_dword(pcr, PCR_SETTING_REG2, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG2, reg);
	pcr->sd30_drive_sel_3v3 =
		map_sd_drive(rtsx_reg_to_sd30_drive_sel_3v3(reg));
}