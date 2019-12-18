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
struct sprd_pwm_chn {int /*<<< orphan*/  clk_rate; TYPE_1__* clks; } ;
struct sprd_pwm_chip {int num_pwms; int /*<<< orphan*/  dev; struct sprd_pwm_chn* chn; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {struct clk* clk; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int EPROBE_DEFER ; 
 int SPRD_PWM_CHN_CLKS_NUM ; 
 int SPRD_PWM_CHN_NUM ; 
 size_t SPRD_PWM_CHN_OUTPUT_CLK ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_clk_bulk_get (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * sprd_pwm_clks ; 

__attribute__((used)) static int sprd_pwm_clk_init(struct sprd_pwm_chip *spc)
{
	struct clk *clk_pwm;
	int ret, i;

	for (i = 0; i < SPRD_PWM_CHN_NUM; i++) {
		struct sprd_pwm_chn *chn = &spc->chn[i];
		int j;

		for (j = 0; j < SPRD_PWM_CHN_CLKS_NUM; ++j)
			chn->clks[j].id =
				sprd_pwm_clks[i * SPRD_PWM_CHN_CLKS_NUM + j];

		ret = devm_clk_bulk_get(spc->dev, SPRD_PWM_CHN_CLKS_NUM,
					chn->clks);
		if (ret) {
			if (ret == -ENOENT)
				break;

			if (ret != -EPROBE_DEFER)
				dev_err(spc->dev,
					"failed to get channel clocks\n");

			return ret;
		}

		clk_pwm = chn->clks[SPRD_PWM_CHN_OUTPUT_CLK].clk;
		chn->clk_rate = clk_get_rate(clk_pwm);
	}

	if (!i) {
		dev_err(spc->dev, "no available PWM channels\n");
		return -ENODEV;
	}

	spc->num_pwms = i;

	return 0;
}