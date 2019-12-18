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
struct dw_pcie {int /*<<< orphan*/ * ops; struct device* dev; } ;
struct meson_pcie {int /*<<< orphan*/  reset_gpio; struct dw_pcie pci; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct meson_pcie* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_ops ; 
 int meson_add_pcie_port (struct meson_pcie*,struct platform_device*) ; 
 int meson_pcie_get_mems (struct platform_device*,struct meson_pcie*) ; 
 int meson_pcie_get_resets (struct meson_pcie*) ; 
 int /*<<< orphan*/  meson_pcie_power_on (struct meson_pcie*) ; 
 int meson_pcie_probe_clocks (struct meson_pcie*) ; 
 int /*<<< orphan*/  meson_pcie_reset (struct meson_pcie*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_pcie*) ; 

__attribute__((used)) static int meson_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct dw_pcie *pci;
	struct meson_pcie *mp;
	int ret;

	mp = devm_kzalloc(dev, sizeof(*mp), GFP_KERNEL);
	if (!mp)
		return -ENOMEM;

	pci = &mp->pci;
	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	mp->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(mp->reset_gpio)) {
		dev_err(dev, "get reset gpio failed\n");
		return PTR_ERR(mp->reset_gpio);
	}

	ret = meson_pcie_get_resets(mp);
	if (ret) {
		dev_err(dev, "get reset resource failed, %d\n", ret);
		return ret;
	}

	ret = meson_pcie_get_mems(pdev, mp);
	if (ret) {
		dev_err(dev, "get memory resource failed, %d\n", ret);
		return ret;
	}

	meson_pcie_power_on(mp);
	meson_pcie_reset(mp);

	ret = meson_pcie_probe_clocks(mp);
	if (ret) {
		dev_err(dev, "init clock resources failed, %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, mp);

	ret = meson_add_pcie_port(mp, pdev);
	if (ret < 0) {
		dev_err(dev, "Add PCIe port failed, %d\n", ret);
		return ret;
	}

	return 0;
}