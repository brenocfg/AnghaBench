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
struct TYPE_2__ {struct device* parent; } ;
struct rproc {int bootaddr; scalar_t__ priv; TYPE_1__ dev; } ;
struct reset_control {int dummy; } ;
struct device {int dummy; } ;
struct da8xx_rproc {int /*<<< orphan*/  bootreg; struct reset_control* dsp_reset; struct clk* dsp_clk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da8xx_rproc_start(struct rproc *rproc)
{
	struct device *dev = rproc->dev.parent;
	struct da8xx_rproc *drproc = (struct da8xx_rproc *)rproc->priv;
	struct clk *dsp_clk = drproc->dsp_clk;
	struct reset_control *dsp_reset = drproc->dsp_reset;
	int ret;

	/* hw requires the start (boot) address be on 1KB boundary */
	if (rproc->bootaddr & 0x3ff) {
		dev_err(dev, "invalid boot address: must be aligned to 1KB\n");

		return -EINVAL;
	}

	writel(rproc->bootaddr, drproc->bootreg);

	ret = clk_prepare_enable(dsp_clk);
	if (ret) {
		dev_err(dev, "clk_prepare_enable() failed: %d\n", ret);
		return ret;
	}

	ret = reset_control_deassert(dsp_reset);
	if (ret) {
		dev_err(dev, "reset_control_deassert() failed: %d\n", ret);
		clk_disable_unprepare(dsp_clk);
		return ret;
	}

	return 0;
}