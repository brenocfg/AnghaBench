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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * notifier_call; } ;
struct tilcdc_drm_private {int is_componentized; char const* max_bandwidth; char const* max_width; char const* max_pixelclock; int rev; scalar_t__ num_encoders; scalar_t__ num_connectors; int is_registered; int /*<<< orphan*/  external_connector; TYPE_1__ freq_transition; void* num_pixelformats; void* pixelformats; struct drm_device* clk; int /*<<< orphan*/  mmio; int /*<<< orphan*/  wq; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct drm_driver {int dummy; } ;
struct drm_device {struct tilcdc_drm_private* dev_private; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  LCDC_PID_REG ; 
 int PTR_ERR (struct drm_device*) ; 
 char const* TILCDC_DEFAULT_MAX_BANDWIDTH ; 
 char const* TILCDC_DEFAULT_MAX_PIXELCLOCK ; 
 char const* TILCDC_DEFAULT_MAX_WIDTH ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 struct drm_device* clk_get (struct device*,char*) ; 
 int component_bind_all (struct device*,struct drm_device*) ; 
 int cpufreq_register_notifier (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cpufreq_transition ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct tilcdc_drm_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct drm_device* drm_dev_alloc (struct drm_driver*,struct device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 
 int drm_irq_install (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modeset_init (struct drm_device*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct drm_device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int tilcdc_add_component_encoder (struct drm_device*) ; 
 int tilcdc_attach_external_device (struct drm_device*) ; 
 void* tilcdc_crossed_formats ; 
 int tilcdc_crtc_create (struct drm_device*) ; 
 int /*<<< orphan*/  tilcdc_fini (struct drm_device*) ; 
 scalar_t__ tilcdc_get_external_components (struct device*,int /*<<< orphan*/ *) ; 
 void* tilcdc_legacy_formats ; 
 int tilcdc_read (struct drm_device*,int /*<<< orphan*/ ) ; 
 void* tilcdc_rev1_formats ; 
 void* tilcdc_straight_formats ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int tilcdc_init(struct drm_driver *ddrv, struct device *dev)
{
	struct drm_device *ddev;
	struct platform_device *pdev = to_platform_device(dev);
	struct device_node *node = dev->of_node;
	struct tilcdc_drm_private *priv;
	struct resource *res;
	u32 bpp = 0;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ddev = drm_dev_alloc(ddrv, dev);
	if (IS_ERR(ddev))
		return PTR_ERR(ddev);

	ddev->dev_private = priv;
	platform_set_drvdata(pdev, ddev);
	drm_mode_config_init(ddev);

	priv->is_componentized =
		tilcdc_get_external_components(dev, NULL) > 0;

	priv->wq = alloc_ordered_workqueue("tilcdc", 0);
	if (!priv->wq) {
		ret = -ENOMEM;
		goto init_failed;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "failed to get memory resource\n");
		ret = -EINVAL;
		goto init_failed;
	}

	priv->mmio = ioremap_nocache(res->start, resource_size(res));
	if (!priv->mmio) {
		dev_err(dev, "failed to ioremap\n");
		ret = -ENOMEM;
		goto init_failed;
	}

	priv->clk = clk_get(dev, "fck");
	if (IS_ERR(priv->clk)) {
		dev_err(dev, "failed to get functional clock\n");
		ret = -ENODEV;
		goto init_failed;
	}

	if (of_property_read_u32(node, "max-bandwidth", &priv->max_bandwidth))
		priv->max_bandwidth = TILCDC_DEFAULT_MAX_BANDWIDTH;

	DBG("Maximum Bandwidth Value %d", priv->max_bandwidth);

	if (of_property_read_u32(node, "max-width", &priv->max_width))
		priv->max_width = TILCDC_DEFAULT_MAX_WIDTH;

	DBG("Maximum Horizontal Pixel Width Value %dpixels", priv->max_width);

	if (of_property_read_u32(node, "max-pixelclock",
					&priv->max_pixelclock))
		priv->max_pixelclock = TILCDC_DEFAULT_MAX_PIXELCLOCK;

	DBG("Maximum Pixel Clock Value %dKHz", priv->max_pixelclock);

	pm_runtime_enable(dev);

	/* Determine LCD IP Version */
	pm_runtime_get_sync(dev);
	switch (tilcdc_read(ddev, LCDC_PID_REG)) {
	case 0x4c100102:
		priv->rev = 1;
		break;
	case 0x4f200800:
	case 0x4f201000:
		priv->rev = 2;
		break;
	default:
		dev_warn(dev, "Unknown PID Reg value 0x%08x, "
			"defaulting to LCD revision 1\n",
			tilcdc_read(ddev, LCDC_PID_REG));
		priv->rev = 1;
		break;
	}

	pm_runtime_put_sync(dev);

	if (priv->rev == 1) {
		DBG("Revision 1 LCDC supports only RGB565 format");
		priv->pixelformats = tilcdc_rev1_formats;
		priv->num_pixelformats = ARRAY_SIZE(tilcdc_rev1_formats);
		bpp = 16;
	} else {
		const char *str = "\0";

		of_property_read_string(node, "blue-and-red-wiring", &str);
		if (0 == strcmp(str, "crossed")) {
			DBG("Configured for crossed blue and red wires");
			priv->pixelformats = tilcdc_crossed_formats;
			priv->num_pixelformats =
				ARRAY_SIZE(tilcdc_crossed_formats);
			bpp = 32; /* Choose bpp with RGB support for fbdef */
		} else if (0 == strcmp(str, "straight")) {
			DBG("Configured for straight blue and red wires");
			priv->pixelformats = tilcdc_straight_formats;
			priv->num_pixelformats =
				ARRAY_SIZE(tilcdc_straight_formats);
			bpp = 16; /* Choose bpp with RGB support for fbdef */
		} else {
			DBG("Blue and red wiring '%s' unknown, use legacy mode",
			    str);
			priv->pixelformats = tilcdc_legacy_formats;
			priv->num_pixelformats =
				ARRAY_SIZE(tilcdc_legacy_formats);
			bpp = 16; /* This is just a guess */
		}
	}

	ret = tilcdc_crtc_create(ddev);
	if (ret < 0) {
		dev_err(dev, "failed to create crtc\n");
		goto init_failed;
	}
	modeset_init(ddev);

#ifdef CONFIG_CPU_FREQ
	priv->freq_transition.notifier_call = cpufreq_transition;
	ret = cpufreq_register_notifier(&priv->freq_transition,
			CPUFREQ_TRANSITION_NOTIFIER);
	if (ret) {
		dev_err(dev, "failed to register cpufreq notifier\n");
		priv->freq_transition.notifier_call = NULL;
		goto init_failed;
	}
#endif

	if (priv->is_componentized) {
		ret = component_bind_all(dev, ddev);
		if (ret < 0)
			goto init_failed;

		ret = tilcdc_add_component_encoder(ddev);
		if (ret < 0)
			goto init_failed;
	} else {
		ret = tilcdc_attach_external_device(ddev);
		if (ret)
			goto init_failed;
	}

	if (!priv->external_connector &&
	    ((priv->num_encoders == 0) || (priv->num_connectors == 0))) {
		dev_err(dev, "no encoders/connectors found\n");
		ret = -EPROBE_DEFER;
		goto init_failed;
	}

	ret = drm_vblank_init(ddev, 1);
	if (ret < 0) {
		dev_err(dev, "failed to initialize vblank\n");
		goto init_failed;
	}

	ret = drm_irq_install(ddev, platform_get_irq(pdev, 0));
	if (ret < 0) {
		dev_err(dev, "failed to install IRQ handler\n");
		goto init_failed;
	}

	drm_mode_config_reset(ddev);

	drm_kms_helper_poll_init(ddev);

	ret = drm_dev_register(ddev, 0);
	if (ret)
		goto init_failed;

	drm_fbdev_generic_setup(ddev, bpp);

	priv->is_registered = true;
	return 0;

init_failed:
	tilcdc_fini(ddev);

	return ret;
}