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
typedef  void* uint32_t ;
struct pp_hwmgr {int dummy; } ;
struct pp_atomfwctrl_bios_boot_up_values {void* ulDClk; void* ulVClk; void* ulEClk; void* ulDCEFClk; void* ulSocClk; int /*<<< orphan*/  ucCoolingID; int /*<<< orphan*/  usVddGfx; int /*<<< orphan*/  usMvddc; int /*<<< orphan*/  usVddci; int /*<<< orphan*/  usVddc; int /*<<< orphan*/  ulUClk; int /*<<< orphan*/  ulGfxClk; int /*<<< orphan*/  ulRevision; } ;
struct atom_firmware_info_v3_1 {int /*<<< orphan*/  coolingsolution_id; int /*<<< orphan*/  bootup_vddgfx_mv; int /*<<< orphan*/  bootup_mvddc_mv; int /*<<< orphan*/  bootup_vddci_mv; int /*<<< orphan*/  bootup_vddc_mv; int /*<<< orphan*/  bootup_mclk_in10khz; int /*<<< orphan*/  bootup_sclk_in10khz; int /*<<< orphan*/  firmware_revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU9_SYSPLL0_DCEFCLK_ID ; 
 int /*<<< orphan*/  SMU9_SYSPLL0_DCLK_ID ; 
 int /*<<< orphan*/  SMU9_SYSPLL0_ECLK_ID ; 
 int /*<<< orphan*/  SMU9_SYSPLL0_SOCCLK_ID ; 
 int /*<<< orphan*/  SMU9_SYSPLL0_VCLK_ID ; 
 int /*<<< orphan*/  pp_atomfwctrl_get_clk_information_by_clkid (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static void pp_atomfwctrl_copy_vbios_bootup_values_3_1(struct pp_hwmgr *hwmgr,
			struct pp_atomfwctrl_bios_boot_up_values *boot_values,
			struct atom_firmware_info_v3_1 *fw_info)
{
	uint32_t frequency = 0;

	boot_values->ulRevision = fw_info->firmware_revision;
	boot_values->ulGfxClk   = fw_info->bootup_sclk_in10khz;
	boot_values->ulUClk     = fw_info->bootup_mclk_in10khz;
	boot_values->usVddc     = fw_info->bootup_vddc_mv;
	boot_values->usVddci    = fw_info->bootup_vddci_mv;
	boot_values->usMvddc    = fw_info->bootup_mvddc_mv;
	boot_values->usVddGfx   = fw_info->bootup_vddgfx_mv;
	boot_values->ucCoolingID = fw_info->coolingsolution_id;
	boot_values->ulSocClk   = 0;
	boot_values->ulDCEFClk   = 0;

	if (!pp_atomfwctrl_get_clk_information_by_clkid(hwmgr, SMU9_SYSPLL0_SOCCLK_ID, 0, &frequency))
		boot_values->ulSocClk   = frequency;

	if (!pp_atomfwctrl_get_clk_information_by_clkid(hwmgr, SMU9_SYSPLL0_DCEFCLK_ID, 0, &frequency))
		boot_values->ulDCEFClk  = frequency;

	if (!pp_atomfwctrl_get_clk_information_by_clkid(hwmgr, SMU9_SYSPLL0_ECLK_ID, 0, &frequency))
		boot_values->ulEClk     = frequency;

	if (!pp_atomfwctrl_get_clk_information_by_clkid(hwmgr, SMU9_SYSPLL0_VCLK_ID, 0, &frequency))
		boot_values->ulVClk     = frequency;

	if (!pp_atomfwctrl_get_clk_information_by_clkid(hwmgr, SMU9_SYSPLL0_DCLK_ID, 0, &frequency))
		boot_values->ulDClk     = frequency;
}