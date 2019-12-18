#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  base; int /*<<< orphan*/  type; } ;
struct vc4_dpi_encoder {TYPE_1__ base; struct vc4_dpi* dpi; } ;
struct TYPE_4__ {int /*<<< orphan*/  nregs; int /*<<< orphan*/  regs; void* base; } ;
struct vc4_dpi {void* core_clock; int /*<<< orphan*/ * encoder; TYPE_2__ regset; void* pixel_clock; void* regs; struct platform_device* pdev; } ;
struct vc4_dev {struct vc4_dpi* dpi; } ;
struct platform_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPI_ID ; 
 scalar_t__ DPI_ID_VALUE ; 
 scalar_t__ DPI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DPI ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  VC4_ENCODER_TYPE_DPI ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,scalar_t__) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct vc4_dpi*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpi_regs ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_debugfs_add_regset32 (struct drm_device*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  vc4_dpi_encoder_funcs ; 
 int /*<<< orphan*/  vc4_dpi_encoder_helper_funcs ; 
 int vc4_dpi_init_bridge (struct vc4_dpi*) ; 
 void* vc4_ioremap_regs (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc4_dpi_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = to_vc4_dev(drm);
	struct vc4_dpi *dpi;
	struct vc4_dpi_encoder *vc4_dpi_encoder;
	int ret;

	dpi = devm_kzalloc(dev, sizeof(*dpi), GFP_KERNEL);
	if (!dpi)
		return -ENOMEM;

	vc4_dpi_encoder = devm_kzalloc(dev, sizeof(*vc4_dpi_encoder),
				       GFP_KERNEL);
	if (!vc4_dpi_encoder)
		return -ENOMEM;
	vc4_dpi_encoder->base.type = VC4_ENCODER_TYPE_DPI;
	vc4_dpi_encoder->dpi = dpi;
	dpi->encoder = &vc4_dpi_encoder->base.base;

	dpi->pdev = pdev;
	dpi->regs = vc4_ioremap_regs(pdev, 0);
	if (IS_ERR(dpi->regs))
		return PTR_ERR(dpi->regs);
	dpi->regset.base = dpi->regs;
	dpi->regset.regs = dpi_regs;
	dpi->regset.nregs = ARRAY_SIZE(dpi_regs);

	if (DPI_READ(DPI_ID) != DPI_ID_VALUE) {
		dev_err(dev, "Port returned 0x%08x for ID instead of 0x%08x\n",
			DPI_READ(DPI_ID), DPI_ID_VALUE);
		return -ENODEV;
	}

	dpi->core_clock = devm_clk_get(dev, "core");
	if (IS_ERR(dpi->core_clock)) {
		ret = PTR_ERR(dpi->core_clock);
		if (ret != -EPROBE_DEFER)
			DRM_ERROR("Failed to get core clock: %d\n", ret);
		return ret;
	}
	dpi->pixel_clock = devm_clk_get(dev, "pixel");
	if (IS_ERR(dpi->pixel_clock)) {
		ret = PTR_ERR(dpi->pixel_clock);
		if (ret != -EPROBE_DEFER)
			DRM_ERROR("Failed to get pixel clock: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(dpi->core_clock);
	if (ret)
		DRM_ERROR("Failed to turn on core clock: %d\n", ret);

	drm_encoder_init(drm, dpi->encoder, &vc4_dpi_encoder_funcs,
			 DRM_MODE_ENCODER_DPI, NULL);
	drm_encoder_helper_add(dpi->encoder, &vc4_dpi_encoder_helper_funcs);

	ret = vc4_dpi_init_bridge(dpi);
	if (ret)
		goto err_destroy_encoder;

	dev_set_drvdata(dev, dpi);

	vc4->dpi = dpi;

	vc4_debugfs_add_regset32(drm, "dpi_regs", &dpi->regset);

	return 0;

err_destroy_encoder:
	drm_encoder_cleanup(dpi->encoder);
	clk_disable_unprepare(dpi->core_clock);
	return ret;
}