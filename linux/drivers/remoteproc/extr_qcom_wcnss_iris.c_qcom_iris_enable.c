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
struct qcom_iris {int /*<<< orphan*/  vregs; int /*<<< orphan*/  num_vregs; int /*<<< orphan*/  dev; int /*<<< orphan*/  xo_clk; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qcom_iris_enable(struct qcom_iris *iris)
{
	int ret;

	ret = regulator_bulk_enable(iris->num_vregs, iris->vregs);
	if (ret)
		return ret;

	ret = clk_prepare_enable(iris->xo_clk);
	if (ret) {
		dev_err(iris->dev, "failed to enable xo clk\n");
		goto disable_regulators;
	}

	return 0;

disable_regulators:
	regulator_bulk_disable(iris->num_vregs, iris->vregs);

	return ret;
}