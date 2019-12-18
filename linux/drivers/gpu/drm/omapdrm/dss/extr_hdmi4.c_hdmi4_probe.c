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
struct omap_hdmi {int /*<<< orphan*/  vdda_reg; int /*<<< orphan*/  core; int /*<<< orphan*/  phy; int /*<<< orphan*/  wp; int /*<<< orphan*/  audio_playing_lock; int /*<<< orphan*/  lock; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int component_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct omap_hdmi*) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi4_component_ops ; 
 int hdmi4_core_init (struct platform_device*,int /*<<< orphan*/ *) ; 
 int hdmi4_init_output (struct omap_hdmi*) ; 
 int hdmi4_probe_of (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi4_uninit_output (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_irq_handler ; 
 int hdmi_phy_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 int hdmi_wp_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct omap_hdmi*) ; 
 struct omap_hdmi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi4_probe(struct platform_device *pdev)
{
	struct omap_hdmi *hdmi;
	int irq;
	int r;

	hdmi = kzalloc(sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return -ENOMEM;

	hdmi->pdev = pdev;

	dev_set_drvdata(&pdev->dev, hdmi);

	mutex_init(&hdmi->lock);
	spin_lock_init(&hdmi->audio_playing_lock);

	r = hdmi4_probe_of(hdmi);
	if (r)
		goto err_free;

	r = hdmi_wp_init(pdev, &hdmi->wp, 4);
	if (r)
		goto err_free;

	r = hdmi_phy_init(pdev, &hdmi->phy, 4);
	if (r)
		goto err_free;

	r = hdmi4_core_init(pdev, &hdmi->core);
	if (r)
		goto err_free;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		DSSERR("platform_get_irq failed\n");
		r = -ENODEV;
		goto err_free;
	}

	r = devm_request_threaded_irq(&pdev->dev, irq,
			NULL, hdmi_irq_handler,
			IRQF_ONESHOT, "OMAP HDMI", hdmi);
	if (r) {
		DSSERR("HDMI IRQ request failed\n");
		goto err_free;
	}

	hdmi->vdda_reg = devm_regulator_get(&pdev->dev, "vdda");
	if (IS_ERR(hdmi->vdda_reg)) {
		r = PTR_ERR(hdmi->vdda_reg);
		if (r != -EPROBE_DEFER)
			DSSERR("can't get VDDA regulator\n");
		goto err_free;
	}

	pm_runtime_enable(&pdev->dev);

	r = hdmi4_init_output(hdmi);
	if (r)
		goto err_pm_disable;

	r = component_add(&pdev->dev, &hdmi4_component_ops);
	if (r)
		goto err_uninit_output;

	return 0;

err_uninit_output:
	hdmi4_uninit_output(hdmi);
err_pm_disable:
	pm_runtime_disable(&pdev->dev);
err_free:
	kfree(hdmi);
	return r;
}