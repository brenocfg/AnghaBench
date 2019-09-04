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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int devm_clk_hw_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_ipq8074_desc ; 
 int /*<<< orphan*/ * gcc_ipq8074_hws ; 
 int qcom_cc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gcc_ipq8074_probe(struct platform_device *pdev)
{
	int ret, i;

	for (i = 0; i < ARRAY_SIZE(gcc_ipq8074_hws); i++) {
		ret = devm_clk_hw_register(&pdev->dev, gcc_ipq8074_hws[i]);
		if (ret)
			return ret;
	}

	return qcom_cc_probe(pdev, &gcc_ipq8074_desc);
}