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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  touch_bit; int /*<<< orphan*/  reset_bus; struct mxc_w1_device* data; } ;
struct mxc_w1_device {scalar_t__ clk; TYPE_1__ bus_master; scalar_t__ regs; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned long,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 scalar_t__ MXC_W1_RESET ; 
 unsigned int MXC_W1_RESET_RST ; 
 scalar_t__ MXC_W1_TIME_DIVIDER ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 unsigned long clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mxc_w1_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxc_w1_ds2_reset_bus ; 
 int /*<<< orphan*/  mxc_w1_ds2_touch_bit ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mxc_w1_device*) ; 
 int w1_add_master_device (TYPE_1__*) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int mxc_w1_probe(struct platform_device *pdev)
{
	struct mxc_w1_device *mdev;
	unsigned long clkrate;
	unsigned int clkdiv;
	int err;

	mdev = devm_kzalloc(&pdev->dev, sizeof(struct mxc_w1_device),
			    GFP_KERNEL);
	if (!mdev)
		return -ENOMEM;

	mdev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(mdev->clk))
		return PTR_ERR(mdev->clk);

	err = clk_prepare_enable(mdev->clk);
	if (err)
		return err;

	clkrate = clk_get_rate(mdev->clk);
	if (clkrate < 10000000)
		dev_warn(&pdev->dev,
			 "Low clock frequency causes improper function\n");

	clkdiv = DIV_ROUND_CLOSEST(clkrate, 1000000);
	clkrate /= clkdiv;
	if ((clkrate < 980000) || (clkrate > 1020000))
		dev_warn(&pdev->dev,
			 "Incorrect time base frequency %lu Hz\n", clkrate);

	mdev->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(mdev->regs)) {
		err = PTR_ERR(mdev->regs);
		goto out_disable_clk;
	}

	/* Software reset 1-Wire module */
	writeb(MXC_W1_RESET_RST, mdev->regs + MXC_W1_RESET);
	writeb(0, mdev->regs + MXC_W1_RESET);

	writeb(clkdiv - 1, mdev->regs + MXC_W1_TIME_DIVIDER);

	mdev->bus_master.data = mdev;
	mdev->bus_master.reset_bus = mxc_w1_ds2_reset_bus;
	mdev->bus_master.touch_bit = mxc_w1_ds2_touch_bit;

	platform_set_drvdata(pdev, mdev);

	err = w1_add_master_device(&mdev->bus_master);
	if (err)
		goto out_disable_clk;

	return 0;

out_disable_clk:
	clk_disable_unprepare(mdev->clk);
	return err;
}