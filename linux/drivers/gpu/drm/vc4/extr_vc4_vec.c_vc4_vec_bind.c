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
struct vc4_vec_encoder {TYPE_1__ base; struct vc4_vec* vec; } ;
struct TYPE_4__ {int /*<<< orphan*/  nregs; int /*<<< orphan*/  regs; int /*<<< orphan*/  base; } ;
struct vc4_vec {int /*<<< orphan*/ * encoder; TYPE_2__ regset; int /*<<< orphan*/  connector; int /*<<< orphan*/  clock; int /*<<< orphan*/  regs; struct platform_device* pdev; } ;
struct vc4_dev {struct vc4_vec* vec; } ;
struct platform_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TVDAC ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC4_ENCODER_TYPE_VEC ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct vc4_vec*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_mode_create_tv_properties (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  tv_mode_names ; 
 int /*<<< orphan*/  vc4_debugfs_add_regset32 (struct drm_device*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  vc4_ioremap_regs (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_vec_connector_init (struct drm_device*,struct vc4_vec*) ; 
 int /*<<< orphan*/  vc4_vec_encoder_funcs ; 
 int /*<<< orphan*/  vc4_vec_encoder_helper_funcs ; 
 int /*<<< orphan*/  vec_regs ; 

__attribute__((used)) static int vc4_vec_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = to_vc4_dev(drm);
	struct vc4_vec *vec;
	struct vc4_vec_encoder *vc4_vec_encoder;
	int ret;

	ret = drm_mode_create_tv_properties(drm, ARRAY_SIZE(tv_mode_names),
					    tv_mode_names);
	if (ret)
		return ret;

	vec = devm_kzalloc(dev, sizeof(*vec), GFP_KERNEL);
	if (!vec)
		return -ENOMEM;

	vc4_vec_encoder = devm_kzalloc(dev, sizeof(*vc4_vec_encoder),
				       GFP_KERNEL);
	if (!vc4_vec_encoder)
		return -ENOMEM;
	vc4_vec_encoder->base.type = VC4_ENCODER_TYPE_VEC;
	vc4_vec_encoder->vec = vec;
	vec->encoder = &vc4_vec_encoder->base.base;

	vec->pdev = pdev;
	vec->regs = vc4_ioremap_regs(pdev, 0);
	if (IS_ERR(vec->regs))
		return PTR_ERR(vec->regs);
	vec->regset.base = vec->regs;
	vec->regset.regs = vec_regs;
	vec->regset.nregs = ARRAY_SIZE(vec_regs);

	vec->clock = devm_clk_get(dev, NULL);
	if (IS_ERR(vec->clock)) {
		ret = PTR_ERR(vec->clock);
		if (ret != -EPROBE_DEFER)
			DRM_ERROR("Failed to get clock: %d\n", ret);
		return ret;
	}

	pm_runtime_enable(dev);

	drm_encoder_init(drm, vec->encoder, &vc4_vec_encoder_funcs,
			 DRM_MODE_ENCODER_TVDAC, NULL);
	drm_encoder_helper_add(vec->encoder, &vc4_vec_encoder_helper_funcs);

	vec->connector = vc4_vec_connector_init(drm, vec);
	if (IS_ERR(vec->connector)) {
		ret = PTR_ERR(vec->connector);
		goto err_destroy_encoder;
	}

	dev_set_drvdata(dev, vec);

	vc4->vec = vec;

	vc4_debugfs_add_regset32(drm, "vec_regs", &vec->regset);

	return 0;

err_destroy_encoder:
	drm_encoder_cleanup(vec->encoder);
	pm_runtime_disable(dev);

	return ret;
}