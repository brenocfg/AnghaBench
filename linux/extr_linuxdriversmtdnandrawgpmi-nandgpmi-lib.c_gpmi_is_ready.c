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
typedef  int uint32_t ;
struct resources {scalar_t__ gpmi_regs; } ;
struct gpmi_nand_data {int /*<<< orphan*/  dev; struct resources resources; } ;

/* Variables and functions */
 scalar_t__ GPMI_IS_MX23 (struct gpmi_nand_data*) ; 
 scalar_t__ GPMI_IS_MX28 (struct gpmi_nand_data*) ; 
 scalar_t__ GPMI_IS_MX6 (struct gpmi_nand_data*) ; 
 scalar_t__ HW_GPMI_DEBUG ; 
 scalar_t__ HW_GPMI_STAT ; 
 unsigned int MX23_BM_GPMI_DEBUG_READY0 ; 
 int MX28_BF_GPMI_STAT_READY_BUSY (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 

int gpmi_is_ready(struct gpmi_nand_data *this, unsigned chip)
{
	struct resources *r = &this->resources;
	uint32_t mask = 0;
	uint32_t reg = 0;

	if (GPMI_IS_MX23(this)) {
		mask = MX23_BM_GPMI_DEBUG_READY0 << chip;
		reg = readl(r->gpmi_regs + HW_GPMI_DEBUG);
	} else if (GPMI_IS_MX28(this) || GPMI_IS_MX6(this)) {
		/*
		 * In the imx6, all the ready/busy pins are bound
		 * together. So we only need to check chip 0.
		 */
		if (GPMI_IS_MX6(this))
			chip = 0;

		/* MX28 shares the same R/B register as MX6Q. */
		mask = MX28_BF_GPMI_STAT_READY_BUSY(1 << chip);
		reg = readl(r->gpmi_regs + HW_GPMI_STAT);
	} else
		dev_err(this->dev, "unknown arch.\n");
	return reg & mask;
}