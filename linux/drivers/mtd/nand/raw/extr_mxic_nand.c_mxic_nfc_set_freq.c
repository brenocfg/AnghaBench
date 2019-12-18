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
struct mxic_nand_ctlr {int dummy; } ;

/* Variables and functions */
 unsigned long MXIC_NFC_MAX_CLK_HZ ; 
 int /*<<< orphan*/  mxic_nfc_clk_disable (struct mxic_nand_ctlr*) ; 
 int mxic_nfc_clk_enable (struct mxic_nand_ctlr*) ; 
 int mxic_nfc_clk_setup (struct mxic_nand_ctlr*,unsigned long) ; 

__attribute__((used)) static int mxic_nfc_set_freq(struct mxic_nand_ctlr *nfc, unsigned long freq)
{
	int ret;

	if (freq > MXIC_NFC_MAX_CLK_HZ)
		freq = MXIC_NFC_MAX_CLK_HZ;

	mxic_nfc_clk_disable(nfc);
	ret = mxic_nfc_clk_setup(nfc, freq);
	if (ret)
		return ret;

	ret = mxic_nfc_clk_enable(nfc);
	if (ret)
		return ret;

	return 0;
}