#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_1__* driver; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {struct mxs_data* data; } ;
struct mxs_ocotp {int /*<<< orphan*/  clk; int /*<<< orphan*/  nvmem; int /*<<< orphan*/  base; } ;
struct mxs_data {int /*<<< orphan*/  size; } ;
struct TYPE_5__ {struct device* dev; struct mxs_ocotp* priv; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct mxs_ocotp* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_nvmem_register (struct device*,TYPE_2__*) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__ ocotp_config ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mxs_ocotp*) ; 

__attribute__((used)) static int mxs_ocotp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct mxs_data *data;
	struct mxs_ocotp *otp;
	const struct of_device_id *match;
	int ret;

	match = of_match_device(dev->driver->of_match_table, dev);
	if (!match || !match->data)
		return -EINVAL;

	otp = devm_kzalloc(dev, sizeof(*otp), GFP_KERNEL);
	if (!otp)
		return -ENOMEM;

	otp->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(otp->base))
		return PTR_ERR(otp->base);

	otp->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(otp->clk))
		return PTR_ERR(otp->clk);

	ret = clk_prepare(otp->clk);
	if (ret < 0) {
		dev_err(dev, "failed to prepare clk: %d\n", ret);
		return ret;
	}

	data = match->data;

	ocotp_config.size = data->size;
	ocotp_config.priv = otp;
	ocotp_config.dev = dev;
	otp->nvmem = devm_nvmem_register(dev, &ocotp_config);
	if (IS_ERR(otp->nvmem)) {
		ret = PTR_ERR(otp->nvmem);
		goto err_clk;
	}

	platform_set_drvdata(pdev, otp);

	return 0;

err_clk:
	clk_unprepare(otp->clk);

	return ret;
}