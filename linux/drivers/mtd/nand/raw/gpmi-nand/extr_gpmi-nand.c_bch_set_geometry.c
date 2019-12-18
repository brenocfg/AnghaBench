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
struct resources {scalar_t__ bch_regs; } ;
struct gpmi_nand_data {int /*<<< orphan*/  dev; struct resources resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPMI_IS_MXS (struct gpmi_nand_data*) ; 
 scalar_t__ HW_BCH_LAYOUTSELECT ; 
 int common_nfc_set_geometry (struct gpmi_nand_data*) ; 
 int gpmi_reset_block (scalar_t__,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bch_set_geometry(struct gpmi_nand_data *this)
{
	struct resources *r = &this->resources;
	int ret;

	ret = common_nfc_set_geometry(this);
	if (ret)
		return ret;

	ret = pm_runtime_get_sync(this->dev);
	if (ret < 0)
		return ret;

	/*
	* Due to erratum #2847 of the MX23, the BCH cannot be soft reset on this
	* chip, otherwise it will lock up. So we skip resetting BCH on the MX23.
	* and MX28.
	*/
	ret = gpmi_reset_block(r->bch_regs, GPMI_IS_MXS(this));
	if (ret)
		goto err_out;

	/* Set *all* chip selects to use layout 0. */
	writel(0, r->bch_regs + HW_BCH_LAYOUTSELECT);

	ret = 0;
err_out:
	pm_runtime_mark_last_busy(this->dev);
	pm_runtime_put_autosuspend(this->dev);

	return ret;
}