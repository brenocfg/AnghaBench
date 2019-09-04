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
struct gpmi_nand_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPMI_NAND_BCH_REGS_ADDR_RES_NAME ; 
 int /*<<< orphan*/  GPMI_NAND_GPMI_REGS_ADDR_RES_NAME ; 
 int acquire_bch_irq (struct gpmi_nand_data*,int /*<<< orphan*/ ) ; 
 int acquire_dma_channels (struct gpmi_nand_data*) ; 
 int acquire_register_block (struct gpmi_nand_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_irq ; 
 int gpmi_get_clks (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  release_dma_channels (struct gpmi_nand_data*) ; 

__attribute__((used)) static int acquire_resources(struct gpmi_nand_data *this)
{
	int ret;

	ret = acquire_register_block(this, GPMI_NAND_GPMI_REGS_ADDR_RES_NAME);
	if (ret)
		goto exit_regs;

	ret = acquire_register_block(this, GPMI_NAND_BCH_REGS_ADDR_RES_NAME);
	if (ret)
		goto exit_regs;

	ret = acquire_bch_irq(this, bch_irq);
	if (ret)
		goto exit_regs;

	ret = acquire_dma_channels(this);
	if (ret)
		goto exit_regs;

	ret = gpmi_get_clks(this);
	if (ret)
		goto exit_clock;
	return 0;

exit_clock:
	release_dma_channels(this);
exit_regs:
	return ret;
}