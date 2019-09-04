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
struct omap_hdmi {int /*<<< orphan*/  pll; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  wp; int /*<<< orphan*/  core; int /*<<< orphan*/  phy; int /*<<< orphan*/  audio_playing_lock; int /*<<< orphan*/  lock; struct dss_device* dss; struct platform_device* pdev; } ;
struct dss_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct omap_hdmi*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct omap_hdmi*) ; 
 int /*<<< orphan*/  dss_debugfs_create_file (struct dss_device*,char*,int /*<<< orphan*/ ,struct omap_hdmi*) ; 
 struct dss_device* dss_get_device (struct device*) ; 
 int hdmi4_cec_init (struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hdmi4_core_init (struct platform_device*,int /*<<< orphan*/ *) ; 
 int hdmi_audio_register (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_dump_regs ; 
 int /*<<< orphan*/  hdmi_init_output (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_irq_handler ; 
 int hdmi_phy_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 int hdmi_pll_init (struct dss_device*,struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_pll_uninit (int /*<<< orphan*/ *) ; 
 int hdmi_probe_of (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_uninit_output (struct omap_hdmi*) ; 
 int hdmi_wp_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct omap_hdmi*) ; 
 struct omap_hdmi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int hdmi4_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct dss_device *dss = dss_get_device(master);
	struct omap_hdmi *hdmi;
	int r;
	int irq;

	hdmi = kzalloc(sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return -ENOMEM;

	hdmi->pdev = pdev;
	hdmi->dss = dss;
	dev_set_drvdata(&pdev->dev, hdmi);

	mutex_init(&hdmi->lock);
	spin_lock_init(&hdmi->audio_playing_lock);

	r = hdmi_probe_of(hdmi);
	if (r)
		goto err_free;

	r = hdmi_wp_init(pdev, &hdmi->wp, 4);
	if (r)
		goto err_free;

	r = hdmi_pll_init(dss, pdev, &hdmi->pll, &hdmi->wp);
	if (r)
		goto err_free;

	r = hdmi_phy_init(pdev, &hdmi->phy, 4);
	if (r)
		goto err_pll;

	r = hdmi4_core_init(pdev, &hdmi->core);
	if (r)
		goto err_pll;

	r = hdmi4_cec_init(pdev, &hdmi->core, &hdmi->wp);
	if (r)
		goto err_pll;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		DSSERR("platform_get_irq failed\n");
		r = -ENODEV;
		goto err_pll;
	}

	r = devm_request_threaded_irq(&pdev->dev, irq,
			NULL, hdmi_irq_handler,
			IRQF_ONESHOT, "OMAP HDMI", hdmi);
	if (r) {
		DSSERR("HDMI IRQ request failed\n");
		goto err_pll;
	}

	pm_runtime_enable(&pdev->dev);

	hdmi_init_output(hdmi);

	r = hdmi_audio_register(hdmi);
	if (r) {
		DSSERR("Registering HDMI audio failed\n");
		hdmi_uninit_output(hdmi);
		pm_runtime_disable(&pdev->dev);
		return r;
	}

	hdmi->debugfs = dss_debugfs_create_file(dss, "hdmi", hdmi_dump_regs,
					       hdmi);

	return 0;

err_pll:
	hdmi_pll_uninit(&hdmi->pll);
err_free:
	kfree(hdmi);
	return r;
}