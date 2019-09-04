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
struct resource {int /*<<< orphan*/  start; } ;
struct mixer_context {int /*<<< orphan*/ * vp_regs; TYPE_1__* pdev; scalar_t__ sclk_hdmi; void* mout_mixer; void* sclk_mixer; int /*<<< orphan*/  flags; void* vp; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MXR_BIT_HAS_SCLK ; 
 int /*<<< orphan*/  clk_set_parent (void*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vp_resources_init(struct mixer_context *mixer_ctx)
{
	struct device *dev = &mixer_ctx->pdev->dev;
	struct resource *res;

	mixer_ctx->vp = devm_clk_get(dev, "vp");
	if (IS_ERR(mixer_ctx->vp)) {
		dev_err(dev, "failed to get clock 'vp'\n");
		return -ENODEV;
	}

	if (test_bit(MXR_BIT_HAS_SCLK, &mixer_ctx->flags)) {
		mixer_ctx->sclk_mixer = devm_clk_get(dev, "sclk_mixer");
		if (IS_ERR(mixer_ctx->sclk_mixer)) {
			dev_err(dev, "failed to get clock 'sclk_mixer'\n");
			return -ENODEV;
		}
		mixer_ctx->mout_mixer = devm_clk_get(dev, "mout_mixer");
		if (IS_ERR(mixer_ctx->mout_mixer)) {
			dev_err(dev, "failed to get clock 'mout_mixer'\n");
			return -ENODEV;
		}

		if (mixer_ctx->sclk_hdmi && mixer_ctx->mout_mixer)
			clk_set_parent(mixer_ctx->mout_mixer,
				       mixer_ctx->sclk_hdmi);
	}

	res = platform_get_resource(mixer_ctx->pdev, IORESOURCE_MEM, 1);
	if (res == NULL) {
		dev_err(dev, "get memory resource failed.\n");
		return -ENXIO;
	}

	mixer_ctx->vp_regs = devm_ioremap(dev, res->start,
							resource_size(res));
	if (mixer_ctx->vp_regs == NULL) {
		dev_err(dev, "register mapping failed.\n");
		return -ENXIO;
	}

	return 0;
}