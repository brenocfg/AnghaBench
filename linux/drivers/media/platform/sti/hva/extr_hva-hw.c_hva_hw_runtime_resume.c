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
struct hva_dev {int /*<<< orphan*/  clk; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_RATE ; 
 int EINVAL ; 
 int /*<<< orphan*/  HVA_PREFIX ; 
 scalar_t__ clk_prepare_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct hva_dev* dev_get_drvdata (struct device*) ; 

int hva_hw_runtime_resume(struct device *dev)
{
	struct hva_dev *hva = dev_get_drvdata(dev);

	if (clk_prepare_enable(hva->clk)) {
		dev_err(hva->dev, "%s     failed to prepare hva clk\n",
			HVA_PREFIX);
		return -EINVAL;
	}

	if (clk_set_rate(hva->clk, CLK_RATE)) {
		dev_err(dev, "%s     failed to set clock frequency\n",
			HVA_PREFIX);
		return -EINVAL;
	}

	return 0;
}