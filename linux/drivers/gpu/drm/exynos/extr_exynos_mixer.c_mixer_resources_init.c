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
struct mixer_context {int /*<<< orphan*/  irq; TYPE_1__* pdev; int /*<<< orphan*/ * mixer_regs; void* sclk_hdmi; void* hdmi; void* mixer; int /*<<< orphan*/  reg_slock; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mixer_context*) ; 
 int /*<<< orphan*/  mixer_irq_handler ; 
 struct resource* platform_get_resource (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mixer_resources_init(struct mixer_context *mixer_ctx)
{
	struct device *dev = &mixer_ctx->pdev->dev;
	struct resource *res;
	int ret;

	spin_lock_init(&mixer_ctx->reg_slock);

	mixer_ctx->mixer = devm_clk_get(dev, "mixer");
	if (IS_ERR(mixer_ctx->mixer)) {
		dev_err(dev, "failed to get clock 'mixer'\n");
		return -ENODEV;
	}

	mixer_ctx->hdmi = devm_clk_get(dev, "hdmi");
	if (IS_ERR(mixer_ctx->hdmi)) {
		dev_err(dev, "failed to get clock 'hdmi'\n");
		return PTR_ERR(mixer_ctx->hdmi);
	}

	mixer_ctx->sclk_hdmi = devm_clk_get(dev, "sclk_hdmi");
	if (IS_ERR(mixer_ctx->sclk_hdmi)) {
		dev_err(dev, "failed to get clock 'sclk_hdmi'\n");
		return -ENODEV;
	}
	res = platform_get_resource(mixer_ctx->pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(dev, "get memory resource failed.\n");
		return -ENXIO;
	}

	mixer_ctx->mixer_regs = devm_ioremap(dev, res->start,
							resource_size(res));
	if (mixer_ctx->mixer_regs == NULL) {
		dev_err(dev, "register mapping failed.\n");
		return -ENXIO;
	}

	res = platform_get_resource(mixer_ctx->pdev, IORESOURCE_IRQ, 0);
	if (res == NULL) {
		dev_err(dev, "get interrupt resource failed.\n");
		return -ENXIO;
	}

	ret = devm_request_irq(dev, res->start, mixer_irq_handler,
						0, "drm_mixer", mixer_ctx);
	if (ret) {
		dev_err(dev, "request interrupt failed.\n");
		return ret;
	}
	mixer_ctx->irq = res->start;

	return 0;
}