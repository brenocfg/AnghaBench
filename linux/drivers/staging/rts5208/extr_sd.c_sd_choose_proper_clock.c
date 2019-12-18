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
struct sd_info {int sd_clock; } ;
struct rtsx_chip {int asic_sd_sdr104_clk; int fpga_sd_sdr104_clk; int asic_sd_ddr50_clk; int fpga_sd_ddr50_clk; int asic_sd_sdr50_clk; int fpga_sd_sdr50_clk; int asic_sd_hs_clk; int fpga_sd_hs_clk; int asic_mmc_52m_clk; int fpga_mmc_52m_clk; scalar_t__ asic_code; struct sd_info sd_card; } ;

/* Variables and functions */
 scalar_t__ CHK_MMC_26M (struct sd_info*) ; 
 scalar_t__ CHK_MMC_52M (struct sd_info*) ; 
 scalar_t__ CHK_MMC_DDR52 (struct sd_info*) ; 
 scalar_t__ CHK_SD_DDR50 (struct sd_info*) ; 
 scalar_t__ CHK_SD_HS (struct sd_info*) ; 
 scalar_t__ CHK_SD_SDR104 (struct sd_info*) ; 
 scalar_t__ CHK_SD_SDR50 (struct sd_info*) ; 
 int CLK_50 ; 

__attribute__((used)) static void sd_choose_proper_clock(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;

	if (CHK_SD_SDR104(sd_card)) {
		if (chip->asic_code)
			sd_card->sd_clock = chip->asic_sd_sdr104_clk;
		else
			sd_card->sd_clock = chip->fpga_sd_sdr104_clk;

	} else if (CHK_SD_DDR50(sd_card)) {
		if (chip->asic_code)
			sd_card->sd_clock = chip->asic_sd_ddr50_clk;
		else
			sd_card->sd_clock = chip->fpga_sd_ddr50_clk;

	} else if (CHK_SD_SDR50(sd_card)) {
		if (chip->asic_code)
			sd_card->sd_clock = chip->asic_sd_sdr50_clk;
		else
			sd_card->sd_clock = chip->fpga_sd_sdr50_clk;

	} else if (CHK_SD_HS(sd_card)) {
		if (chip->asic_code)
			sd_card->sd_clock = chip->asic_sd_hs_clk;
		else
			sd_card->sd_clock = chip->fpga_sd_hs_clk;

	} else if (CHK_MMC_52M(sd_card) || CHK_MMC_DDR52(sd_card)) {
		if (chip->asic_code)
			sd_card->sd_clock = chip->asic_mmc_52m_clk;
		else
			sd_card->sd_clock = chip->fpga_mmc_52m_clk;

	} else if (CHK_MMC_26M(sd_card)) {
		if (chip->asic_code)
			sd_card->sd_clock = 48;
		else
			sd_card->sd_clock = CLK_50;
	}
}