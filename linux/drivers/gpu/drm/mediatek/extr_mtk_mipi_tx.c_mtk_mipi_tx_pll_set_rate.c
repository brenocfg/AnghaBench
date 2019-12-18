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
struct mtk_mipi_tx {unsigned long data_rate; int /*<<< orphan*/  dev; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 struct mtk_mipi_tx* mtk_mipi_tx_from_clk_hw (struct clk_hw*) ; 

__attribute__((used)) static int mtk_mipi_tx_pll_set_rate(struct clk_hw *hw, unsigned long rate,
				    unsigned long parent_rate)
{
	struct mtk_mipi_tx *mipi_tx = mtk_mipi_tx_from_clk_hw(hw);

	dev_dbg(mipi_tx->dev, "set rate: %lu Hz\n", rate);

	mipi_tx->data_rate = rate;

	return 0;
}