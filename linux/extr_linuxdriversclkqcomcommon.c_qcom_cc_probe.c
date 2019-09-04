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
struct regmap {int dummy; } ;
struct qcom_cc_desc {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* qcom_cc_map (struct platform_device*,struct qcom_cc_desc const*) ; 
 int qcom_cc_really_probe (struct platform_device*,struct qcom_cc_desc const*,struct regmap*) ; 

int qcom_cc_probe(struct platform_device *pdev, const struct qcom_cc_desc *desc)
{
	struct regmap *regmap;

	regmap = qcom_cc_map(pdev, desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	return qcom_cc_really_probe(pdev, desc, regmap);
}