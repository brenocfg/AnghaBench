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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * init; } ;
struct hdmi_pll_8996 {TYPE_1__ clk_hw; struct clk** mmio_qserdes_tx; struct clk* mmio_qserdes_com; struct platform_device* pdev; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  label ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HDMI_NUM_TX_CHANNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 struct clk* devm_clk_register (struct device*,TYPE_1__*) ; 
 struct hdmi_pll_8996* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* msm_ioremap (struct platform_device*,char*,char*) ; 
 int /*<<< orphan*/  pll_init ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int msm_hdmi_pll_8996_init(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hdmi_pll_8996 *pll;
	struct clk *clk;
	int i;

	pll = devm_kzalloc(dev, sizeof(*pll), GFP_KERNEL);
	if (!pll)
		return -ENOMEM;

	pll->pdev = pdev;

	pll->mmio_qserdes_com = msm_ioremap(pdev, "hdmi_pll", "HDMI_PLL");
	if (IS_ERR(pll->mmio_qserdes_com)) {
		DRM_DEV_ERROR(dev, "failed to map pll base\n");
		return -ENOMEM;
	}

	for (i = 0; i < HDMI_NUM_TX_CHANNEL; i++) {
		char name[32], label[32];

		snprintf(name, sizeof(name), "hdmi_tx_l%d", i);
		snprintf(label, sizeof(label), "HDMI_TX_L%d", i);

		pll->mmio_qserdes_tx[i] = msm_ioremap(pdev, name, label);
		if (IS_ERR(pll->mmio_qserdes_tx[i])) {
			DRM_DEV_ERROR(dev, "failed to map pll base\n");
			return -ENOMEM;
		}
	}
	pll->clk_hw.init = &pll_init;

	clk = devm_clk_register(dev, &pll->clk_hw);
	if (IS_ERR(clk)) {
		DRM_DEV_ERROR(dev, "failed to register pll clock\n");
		return -EINVAL;
	}

	return 0;
}