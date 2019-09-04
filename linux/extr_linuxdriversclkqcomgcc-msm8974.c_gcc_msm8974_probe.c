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
struct platform_device {struct device dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  gcc_msm8974_desc ; 
 int /*<<< orphan*/  gcc_msm8974_match_table ; 
 int /*<<< orphan*/  msm8974_pro_clock_override () ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int qcom_cc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_register_board_clk (struct device*,char*,char*,int) ; 
 int qcom_cc_register_sleep_clk (struct device*) ; 

__attribute__((used)) static int gcc_msm8974_probe(struct platform_device *pdev)
{
	int ret;
	struct device *dev = &pdev->dev;
	bool pro;
	const struct of_device_id *id;

	id = of_match_device(gcc_msm8974_match_table, dev);
	if (!id)
		return -ENODEV;
	pro = !!(id->data);

	if (pro)
		msm8974_pro_clock_override();

	ret = qcom_cc_register_board_clk(dev, "xo_board", "xo", 19200000);
	if (ret)
		return ret;

	ret = qcom_cc_register_sleep_clk(dev);
	if (ret)
		return ret;

	return qcom_cc_probe(pdev, &gcc_msm8974_desc);
}