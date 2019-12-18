#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct hdmi_audio_infoframe {int channels; int /*<<< orphan*/  sample_frequency; int /*<<< orphan*/  sample_size; int /*<<< orphan*/  coding_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  pdev; struct hdmi_audio_infoframe infoframe; } ;
struct hdmi_context {TYPE_3__* ddc_adpt; scalar_t__ regs_hdmiphy; TYPE_2__* hdmiphy_port; int /*<<< orphan*/ * notifier; TYPE_1__ audio; void* sysreg; TYPE_4__* drv_data; void* pmureg; int /*<<< orphan*/  irq; int /*<<< orphan*/  hotplug_work; void* regs; int /*<<< orphan*/  mutex; struct device* dev; } ;
struct TYPE_8__ {scalar_t__ has_sysreg; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDMI_AUDIO_CODING_TYPE_STREAM ; 
 int /*<<< orphan*/  HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM ; 
 int /*<<< orphan*/  HDMI_AUDIO_SAMPLE_SIZE_STREAM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/ * cec_notifier_get (struct device*) ; 
 int /*<<< orphan*/  cec_notifier_put (int /*<<< orphan*/ *) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct hdmi_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct hdmi_context*) ; 
 int /*<<< orphan*/  hdmi_audio_infoframe_init (struct hdmi_audio_infoframe*) ; 
 int /*<<< orphan*/  hdmi_component_ops ; 
 int hdmi_get_ddc_adapter (struct hdmi_context*) ; 
 int hdmi_get_phy_io (struct hdmi_context*) ; 
 int /*<<< orphan*/  hdmi_hotplug_work_func ; 
 int /*<<< orphan*/  hdmi_irq_thread ; 
 int hdmi_register_audio_device (struct hdmi_context*) ; 
 int hdmi_resources_init (struct hdmi_context*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hdmi_context*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 void* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hdmi_probe(struct platform_device *pdev)
{
	struct hdmi_audio_infoframe *audio_infoframe;
	struct device *dev = &pdev->dev;
	struct hdmi_context *hdata;
	struct resource *res;
	int ret;

	hdata = devm_kzalloc(dev, sizeof(struct hdmi_context), GFP_KERNEL);
	if (!hdata)
		return -ENOMEM;

	hdata->drv_data = of_device_get_match_data(dev);

	platform_set_drvdata(pdev, hdata);

	hdata->dev = dev;

	mutex_init(&hdata->mutex);

	ret = hdmi_resources_init(hdata);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "hdmi_resources_init failed\n");
		return ret;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hdata->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(hdata->regs)) {
		ret = PTR_ERR(hdata->regs);
		return ret;
	}

	ret = hdmi_get_ddc_adapter(hdata);
	if (ret)
		return ret;

	ret = hdmi_get_phy_io(hdata);
	if (ret)
		goto err_ddc;

	INIT_DELAYED_WORK(&hdata->hotplug_work, hdmi_hotplug_work_func);

	ret = devm_request_threaded_irq(dev, hdata->irq, NULL,
			hdmi_irq_thread, IRQF_TRIGGER_RISING |
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			"hdmi", hdata);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to register hdmi interrupt\n");
		goto err_hdmiphy;
	}

	hdata->pmureg = syscon_regmap_lookup_by_phandle(dev->of_node,
			"samsung,syscon-phandle");
	if (IS_ERR(hdata->pmureg)) {
		DRM_DEV_ERROR(dev, "syscon regmap lookup failed.\n");
		ret = -EPROBE_DEFER;
		goto err_hdmiphy;
	}

	if (hdata->drv_data->has_sysreg) {
		hdata->sysreg = syscon_regmap_lookup_by_phandle(dev->of_node,
				"samsung,sysreg-phandle");
		if (IS_ERR(hdata->sysreg)) {
			DRM_DEV_ERROR(dev, "sysreg regmap lookup failed.\n");
			ret = -EPROBE_DEFER;
			goto err_hdmiphy;
		}
	}

	hdata->notifier = cec_notifier_get(&pdev->dev);
	if (hdata->notifier == NULL) {
		ret = -ENOMEM;
		goto err_hdmiphy;
	}

	pm_runtime_enable(dev);

	audio_infoframe = &hdata->audio.infoframe;
	hdmi_audio_infoframe_init(audio_infoframe);
	audio_infoframe->coding_type = HDMI_AUDIO_CODING_TYPE_STREAM;
	audio_infoframe->sample_size = HDMI_AUDIO_SAMPLE_SIZE_STREAM;
	audio_infoframe->sample_frequency = HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM;
	audio_infoframe->channels = 2;

	ret = hdmi_register_audio_device(hdata);
	if (ret)
		goto err_notifier_put;

	ret = component_add(&pdev->dev, &hdmi_component_ops);
	if (ret)
		goto err_unregister_audio;

	return ret;

err_unregister_audio:
	platform_device_unregister(hdata->audio.pdev);

err_notifier_put:
	cec_notifier_put(hdata->notifier);
	pm_runtime_disable(dev);

err_hdmiphy:
	if (hdata->hdmiphy_port)
		put_device(&hdata->hdmiphy_port->dev);
	if (hdata->regs_hdmiphy)
		iounmap(hdata->regs_hdmiphy);
err_ddc:
	put_device(&hdata->ddc_adpt->dev);

	return ret;
}