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
struct input_dev {int dummy; } ;
struct imx6ul_tsc {int /*<<< orphan*/  adc_clk; int /*<<< orphan*/  tsc_clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int imx6ul_tsc_init (struct imx6ul_tsc*) ; 
 struct imx6ul_tsc* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int imx6ul_tsc_open(struct input_dev *input_dev)
{
	struct imx6ul_tsc *tsc = input_get_drvdata(input_dev);
	int err;

	err = clk_prepare_enable(tsc->adc_clk);
	if (err) {
		dev_err(tsc->dev,
			"Could not prepare or enable the adc clock: %d\n",
			err);
		return err;
	}

	err = clk_prepare_enable(tsc->tsc_clk);
	if (err) {
		dev_err(tsc->dev,
			"Could not prepare or enable the tsc clock: %d\n",
			err);
		goto disable_adc_clk;
	}

	err = imx6ul_tsc_init(tsc);
	if (err)
		goto disable_tsc_clk;

	return 0;

disable_tsc_clk:
	clk_disable_unprepare(tsc->tsc_clk);
disable_adc_clk:
	clk_disable_unprepare(tsc->adc_clk);
	return err;
}