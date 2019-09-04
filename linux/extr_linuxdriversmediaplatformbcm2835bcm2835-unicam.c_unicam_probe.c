#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_handler {int dummy; } ;
struct TYPE_3__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct unicam_cfg {void* clk_gate_base; void* base; } ;
struct unicam_device {TYPE_1__ v4l2_dev; struct v4l2_ctrl_handler ctrl_handler; void* clock; struct unicam_cfg cfg; struct platform_device* pdev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct unicam_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct unicam_device*) ; 
 int of_unicam_connect_subdevs (struct unicam_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct unicam_device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unicam_err (struct unicam_device*,char*) ; 
 int /*<<< orphan*/  unicam_isr ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 

__attribute__((used)) static int unicam_probe(struct platform_device *pdev)
{
	struct unicam_cfg *unicam_cfg;
	struct unicam_device *unicam;
	struct v4l2_ctrl_handler *hdl;
	struct resource	*res;
	int ret;

	unicam = devm_kzalloc(&pdev->dev, sizeof(*unicam), GFP_KERNEL);
	if (!unicam)
		return -ENOMEM;

	unicam->pdev = pdev;
	unicam_cfg = &unicam->cfg;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	unicam_cfg->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(unicam_cfg->base)) {
		unicam_err(unicam, "Failed to get main io block\n");
		return PTR_ERR(unicam_cfg->base);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	unicam_cfg->clk_gate_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(unicam_cfg->clk_gate_base)) {
		unicam_err(unicam, "Failed to get 2nd io block\n");
		return PTR_ERR(unicam_cfg->clk_gate_base);
	}

	unicam->clock = devm_clk_get(&pdev->dev, "lp");
	if (IS_ERR(unicam->clock)) {
		unicam_err(unicam, "Failed to get clock\n");
		return PTR_ERR(unicam->clock);
	}

	ret = platform_get_irq(pdev, 0);
	if (ret <= 0) {
		dev_err(&pdev->dev, "No IRQ resource\n");
		return -ENODEV;
	}

	ret = devm_request_irq(&pdev->dev, ret, unicam_isr, 0,
			       "unicam_capture0", unicam);
	if (ret) {
		dev_err(&pdev->dev, "Unable to request interrupt\n");
		return -EINVAL;
	}

	ret = v4l2_device_register(&pdev->dev, &unicam->v4l2_dev);
	if (ret) {
		unicam_err(unicam,
			   "Unable to register v4l2 device.\n");
		return ret;
	}

	/* Reserve space for the controls */
	hdl = &unicam->ctrl_handler;
	ret = v4l2_ctrl_handler_init(hdl, 16);
	if (ret < 0)
		goto probe_out_v4l2_unregister;
	unicam->v4l2_dev.ctrl_handler = hdl;

	/* set the driver data in platform device */
	platform_set_drvdata(pdev, unicam);

	ret = of_unicam_connect_subdevs(unicam);
	if (ret) {
		dev_err(&pdev->dev, "Failed to connect subdevs\n");
		goto free_hdl;
	}

	/* Enable the block power domain */
	pm_runtime_enable(&pdev->dev);

	return 0;

free_hdl:
	v4l2_ctrl_handler_free(hdl);
probe_out_v4l2_unregister:
	v4l2_device_unregister(&unicam->v4l2_dev);
	return ret;
}