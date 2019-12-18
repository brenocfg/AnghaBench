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
struct ms_info {int /*<<< orphan*/  ms_clock; } ;
struct rtsx_chip {int /*<<< orphan*/  fpga_ms_1bit_clk; int /*<<< orphan*/  asic_ms_1bit_clk; scalar_t__ asic_code; int /*<<< orphan*/  fpga_ms_4bit_clk; int /*<<< orphan*/  asic_ms_4bit_clk; int /*<<< orphan*/  fpga_ms_hg_clk; int /*<<< orphan*/  asic_ms_hg_clk; struct ms_info ms_card; } ;

/* Variables and functions */
 scalar_t__ CHK_HG8BIT (struct ms_info*) ; 
 scalar_t__ CHK_MS4BIT (struct ms_info*) ; 
 scalar_t__ CHK_MSPRO (struct ms_info*) ; 
 int /*<<< orphan*/  MS_CARD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int select_card (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int switch_clock (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms_set_init_para(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval;

	if (CHK_HG8BIT(ms_card)) {
		if (chip->asic_code)
			ms_card->ms_clock = chip->asic_ms_hg_clk;
		else
			ms_card->ms_clock = chip->fpga_ms_hg_clk;

	} else if (CHK_MSPRO(ms_card) || CHK_MS4BIT(ms_card)) {
		if (chip->asic_code)
			ms_card->ms_clock = chip->asic_ms_4bit_clk;
		else
			ms_card->ms_clock = chip->fpga_ms_4bit_clk;

	} else {
		if (chip->asic_code)
			ms_card->ms_clock = chip->asic_ms_1bit_clk;
		else
			ms_card->ms_clock = chip->fpga_ms_1bit_clk;
	}

	retval = switch_clock(chip, ms_card->ms_clock);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = select_card(chip, MS_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}