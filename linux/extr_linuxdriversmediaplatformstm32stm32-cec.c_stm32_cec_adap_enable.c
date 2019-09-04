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
struct stm32_cec {int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk_hdmi_cec; int /*<<< orphan*/  clk_cec; int /*<<< orphan*/  dev; } ;
struct cec_adapter {struct stm32_cec* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CECEN ; 
 int /*<<< orphan*/  CEC_CR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct stm32_cec *cec = adap->priv;
	int ret = 0;

	if (enable) {
		ret = clk_enable(cec->clk_cec);
		if (ret)
			dev_err(cec->dev, "fail to enable cec clock\n");

		clk_enable(cec->clk_hdmi_cec);
		regmap_update_bits(cec->regmap, CEC_CR, CECEN, CECEN);
	} else {
		clk_disable(cec->clk_cec);
		clk_disable(cec->clk_hdmi_cec);
		regmap_update_bits(cec->regmap, CEC_CR, CECEN, 0);
	}

	return ret;
}