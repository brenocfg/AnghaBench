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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct meson_ao_cec_device {struct device* adap; int /*<<< orphan*/  notify; struct device* core; struct device* base; struct platform_device* pdev; int /*<<< orphan*/  cec_reg_lock; } ;
struct device {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int CEC_CAP_CONNECTOR_INFO ; 
 int CEC_CAP_DEFAULTS ; 
 int /*<<< orphan*/  CEC_CLK_RATE ; 
 int CEC_GEN_CNTL_REG ; 
 int /*<<< orphan*/  CEC_GEN_CNTL_RESET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct device* cec_allocate_adapter (int /*<<< orphan*/ *,struct meson_ao_cec_device*,char*,int,int) ; 
 int /*<<< orphan*/  cec_delete_adapter (struct device*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_register (struct device*,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_unregister (int /*<<< orphan*/ ) ; 
 struct device* cec_notifier_parse_hdmi_phandle (int /*<<< orphan*/ *) ; 
 int cec_register_adapter (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct device*) ; 
 int clk_prepare_enable (struct device*) ; 
 int clk_set_rate (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_reset_optional (int /*<<< orphan*/ *) ; 
 struct device* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct device* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct meson_ao_cec_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct meson_ao_cec_device*) ; 
 int /*<<< orphan*/  meson_ao_cec_irq ; 
 int /*<<< orphan*/  meson_ao_cec_irq_thread ; 
 int /*<<< orphan*/  meson_ao_cec_ops ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_ao_cec_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static int meson_ao_cec_probe(struct platform_device *pdev)
{
	struct meson_ao_cec_device *ao_cec;
	struct device *hdmi_dev;
	struct resource *res;
	int ret, irq;

	hdmi_dev = cec_notifier_parse_hdmi_phandle(&pdev->dev);

	if (IS_ERR(hdmi_dev))
		return PTR_ERR(hdmi_dev);

	ao_cec = devm_kzalloc(&pdev->dev, sizeof(*ao_cec), GFP_KERNEL);
	if (!ao_cec)
		return -ENOMEM;

	spin_lock_init(&ao_cec->cec_reg_lock);

	ao_cec->adap = cec_allocate_adapter(&meson_ao_cec_ops, ao_cec,
					    "meson_ao_cec",
					    CEC_CAP_DEFAULTS |
					    CEC_CAP_CONNECTOR_INFO,
					    1); /* Use 1 for now */
	if (IS_ERR(ao_cec->adap))
		return PTR_ERR(ao_cec->adap);

	ao_cec->notify = cec_notifier_cec_adap_register(hdmi_dev, NULL,
							ao_cec->adap);
	if (!ao_cec->notify) {
		ret = -ENOMEM;
		goto out_probe_adapter;
	}

	ao_cec->adap->owner = THIS_MODULE;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ao_cec->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ao_cec->base)) {
		ret = PTR_ERR(ao_cec->base);
		goto out_probe_notify;
	}

	irq = platform_get_irq(pdev, 0);
	ret = devm_request_threaded_irq(&pdev->dev, irq,
					meson_ao_cec_irq,
					meson_ao_cec_irq_thread,
					0, NULL, ao_cec);
	if (ret) {
		dev_err(&pdev->dev, "irq request failed\n");
		goto out_probe_notify;
	}

	ao_cec->core = devm_clk_get(&pdev->dev, "core");
	if (IS_ERR(ao_cec->core)) {
		dev_err(&pdev->dev, "core clock request failed\n");
		ret = PTR_ERR(ao_cec->core);
		goto out_probe_notify;
	}

	ret = clk_prepare_enable(ao_cec->core);
	if (ret) {
		dev_err(&pdev->dev, "core clock enable failed\n");
		goto out_probe_notify;
	}

	ret = clk_set_rate(ao_cec->core, CEC_CLK_RATE);
	if (ret) {
		dev_err(&pdev->dev, "core clock set rate failed\n");
		goto out_probe_clk;
	}

	device_reset_optional(&pdev->dev);

	ao_cec->pdev = pdev;
	platform_set_drvdata(pdev, ao_cec);

	ret = cec_register_adapter(ao_cec->adap, &pdev->dev);
	if (ret < 0)
		goto out_probe_clk;

	/* Setup Hardware */
	writel_relaxed(CEC_GEN_CNTL_RESET,
		       ao_cec->base + CEC_GEN_CNTL_REG);

	return 0;

out_probe_clk:
	clk_disable_unprepare(ao_cec->core);

out_probe_notify:
	cec_notifier_cec_adap_unregister(ao_cec->notify);

out_probe_adapter:
	cec_delete_adapter(ao_cec->adap);

	dev_err(&pdev->dev, "CEC controller registration failed\n");

	return ret;
}