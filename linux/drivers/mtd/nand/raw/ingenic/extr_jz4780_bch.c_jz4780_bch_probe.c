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
struct platform_device {int dummy; } ;
struct ingenic_ecc {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCH_CLK_RATE ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ingenic_ecc_probe (struct platform_device*) ; 
 struct ingenic_ecc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int jz4780_bch_probe(struct platform_device *pdev)
{
	struct ingenic_ecc *bch;
	int ret;

	ret = ingenic_ecc_probe(pdev);
	if (ret)
		return ret;

	bch = platform_get_drvdata(pdev);
	clk_set_rate(bch->clk, BCH_CLK_RATE);

	return 0;
}