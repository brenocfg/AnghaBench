#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {int must_apply_timings; } ;
struct gpmi_nand_data {int current_chip; TYPE_1__ hw; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gpmi_disable_clk (struct gpmi_nand_data*) ; 
 int gpmi_enable_clk (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  gpmi_nfc_apply_timings (struct gpmi_nand_data*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void gpmi_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct gpmi_nand_data *this = nand_get_controller_data(chip);
	int ret;

	/*
	 * For power consumption matters, disable/enable the clock each time a
	 * die is selected/unselected.
	 */
	if (this->current_chip < 0 && chipnr >= 0) {
		ret = gpmi_enable_clk(this);
		if (ret)
			dev_err(this->dev, "Failed to enable the clock\n");
	} else if (this->current_chip >= 0 && chipnr < 0) {
		ret = gpmi_disable_clk(this);
		if (ret)
			dev_err(this->dev, "Failed to disable the clock\n");
	}

	/*
	 * This driver currently supports only one NAND chip. Plus, dies share
	 * the same configuration. So once timings have been applied on the
	 * controller side, they will not change anymore. When the time will
	 * come, the check on must_apply_timings will have to be dropped.
	 */
	if (chipnr >= 0 && this->hw.must_apply_timings) {
		this->hw.must_apply_timings = false;
		gpmi_nfc_apply_timings(this);
	}

	this->current_chip = chipnr;
}