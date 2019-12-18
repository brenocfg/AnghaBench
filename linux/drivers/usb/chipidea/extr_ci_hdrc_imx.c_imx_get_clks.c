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
struct ci_hdrc_imx_data {int need_three_clks; void* clk_per; void* clk_ahb; void* clk_ipg; void* clk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct ci_hdrc_imx_data* dev_get_drvdata (struct device*) ; 
 void* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static int imx_get_clks(struct device *dev)
{
	struct ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	int ret = 0;

	data->clk_ipg = devm_clk_get(dev, "ipg");
	if (IS_ERR(data->clk_ipg)) {
		/* If the platform only needs one clocks */
		data->clk = devm_clk_get(dev, NULL);
		if (IS_ERR(data->clk)) {
			ret = PTR_ERR(data->clk);
			dev_err(dev,
				"Failed to get clks, err=%ld,%ld\n",
				PTR_ERR(data->clk), PTR_ERR(data->clk_ipg));
			return ret;
		}
		return ret;
	}

	data->clk_ahb = devm_clk_get(dev, "ahb");
	if (IS_ERR(data->clk_ahb)) {
		ret = PTR_ERR(data->clk_ahb);
		dev_err(dev,
			"Failed to get ahb clock, err=%d\n", ret);
		return ret;
	}

	data->clk_per = devm_clk_get(dev, "per");
	if (IS_ERR(data->clk_per)) {
		ret = PTR_ERR(data->clk_per);
		dev_err(dev,
			"Failed to get per clock, err=%d\n", ret);
		return ret;
	}

	data->need_three_clks = true;
	return ret;
}