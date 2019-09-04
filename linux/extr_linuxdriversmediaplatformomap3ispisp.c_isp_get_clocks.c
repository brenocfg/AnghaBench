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
struct isp_device {struct clk** clock; int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * isp_clocks ; 

__attribute__((used)) static int isp_get_clocks(struct isp_device *isp)
{
	struct clk *clk;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(isp_clocks); ++i) {
		clk = devm_clk_get(isp->dev, isp_clocks[i]);
		if (IS_ERR(clk)) {
			dev_err(isp->dev, "clk_get %s failed\n", isp_clocks[i]);
			return PTR_ERR(clk);
		}

		isp->clock[i] = clk;
	}

	return 0;
}