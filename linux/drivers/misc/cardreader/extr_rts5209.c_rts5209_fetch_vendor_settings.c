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
struct rtsx_pcr {int /*<<< orphan*/  card_drive_sel; int /*<<< orphan*/  sd30_drive_sel_3v3; int /*<<< orphan*/  sd30_drive_sel_1v8; int /*<<< orphan*/  aspm_en; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCR_MS_PMOS ; 
 int /*<<< orphan*/  PCR_SETTING_REG1 ; 
 int /*<<< orphan*/  PCR_SETTING_REG2 ; 
 int /*<<< orphan*/  pcr_dbg (struct rtsx_pcr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rts5209_reg_check_ms_pmos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rts5209_reg_to_aspm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rts5209_reg_to_card_drive_sel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rts5209_reg_to_sd30_drive_sel_1v8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rts5209_reg_to_sd30_drive_sel_3v3 (int /*<<< orphan*/ ) ; 
 scalar_t__ rts5209_vendor_setting1_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ rts5209_vendor_setting2_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_read_config_dword (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rts5209_fetch_vendor_settings(struct rtsx_pcr *pcr)
{
	u32 reg;

	rtsx_pci_read_config_dword(pcr, PCR_SETTING_REG1, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG1, reg);

	if (rts5209_vendor_setting1_valid(reg)) {
		if (rts5209_reg_check_ms_pmos(reg))
			pcr->flags |= PCR_MS_PMOS;
		pcr->aspm_en = rts5209_reg_to_aspm(reg);
	}

	rtsx_pci_read_config_dword(pcr, PCR_SETTING_REG2, &reg);
	pcr_dbg(pcr, "Cfg 0x%x: 0x%x\n", PCR_SETTING_REG2, reg);

	if (rts5209_vendor_setting2_valid(reg)) {
		pcr->sd30_drive_sel_1v8 =
			rts5209_reg_to_sd30_drive_sel_1v8(reg);
		pcr->sd30_drive_sel_3v3 =
			rts5209_reg_to_sd30_drive_sel_3v3(reg);
		pcr->card_drive_sel = rts5209_reg_to_card_drive_sel(reg);
	}
}