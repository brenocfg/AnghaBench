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
struct mtk_nfc_clk {int /*<<< orphan*/  nfi_clk; int /*<<< orphan*/  pad_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int mtk_nfc_enable_clk(struct device *dev, struct mtk_nfc_clk *clk)
{
	int ret;

	ret = clk_prepare_enable(clk->nfi_clk);
	if (ret) {
		dev_err(dev, "failed to enable nfi clk\n");
		return ret;
	}

	ret = clk_prepare_enable(clk->pad_clk);
	if (ret) {
		dev_err(dev, "failed to enable pad clk\n");
		clk_disable_unprepare(clk->nfi_clk);
		return ret;
	}

	return 0;
}