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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pwm_sifive_ddata {int /*<<< orphan*/  clk; TYPE_1__ chip; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct pwm_sifive_ddata* pwm_sifive_chip_to_ddata (struct pwm_chip*) ; 

__attribute__((used)) static int pwm_sifive_enable(struct pwm_chip *chip, bool enable)
{
	struct pwm_sifive_ddata *ddata = pwm_sifive_chip_to_ddata(chip);
	int ret;

	if (enable) {
		ret = clk_enable(ddata->clk);
		if (ret) {
			dev_err(ddata->chip.dev, "Enable clk failed\n");
			return ret;
		}
	}

	if (!enable)
		clk_disable(ddata->clk);

	return 0;
}