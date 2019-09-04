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
struct device {int dummy; } ;
struct adv7511 {int /*<<< orphan*/ * cec_clk; int /*<<< orphan*/  cec_clk_freq; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static int adv7511_cec_parse_dt(struct device *dev, struct adv7511 *adv7511)
{
	adv7511->cec_clk = devm_clk_get(dev, "cec");
	if (IS_ERR(adv7511->cec_clk)) {
		int ret = PTR_ERR(adv7511->cec_clk);

		adv7511->cec_clk = NULL;
		return ret;
	}
	clk_prepare_enable(adv7511->cec_clk);
	adv7511->cec_clk_freq = clk_get_rate(adv7511->cec_clk);
	return 0;
}