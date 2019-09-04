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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct fimd_context {int suspended; int i80_if; int /*<<< orphan*/ * encoder; int /*<<< orphan*/  wait_vsync_event; int /*<<< orphan*/  wait_vsync_queue; int /*<<< orphan*/ * regs; int /*<<< orphan*/ * lcd_clk; int /*<<< orphan*/ * bus_clk; int /*<<< orphan*/ * sysreg; int /*<<< orphan*/  i80ifcon; int /*<<< orphan*/  vidcon0; int /*<<< orphan*/  vidout_con; TYPE_1__* driver_data; int /*<<< orphan*/  vidcon1; struct device* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ has_vidoutcon; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LCD_CS_SETUP (int) ; 
 int /*<<< orphan*/  LCD_WR_ACTIVE (int) ; 
 int /*<<< orphan*/  LCD_WR_HOLD (int) ; 
 int /*<<< orphan*/  LCD_WR_SETUP (int) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIDCON0_DSI_EN ; 
 int /*<<< orphan*/  VIDCON0_VIDOUT_I80_LDI0 ; 
 int /*<<< orphan*/  VIDCON1_INV_VCLK ; 
 int /*<<< orphan*/  VIDCON1_INV_VDEN ; 
 int /*<<< orphan*/  VIDOUT_CON_F_I80_LDI0 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct fimd_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct fimd_context*) ; 
 int /*<<< orphan*/ * exynos_dpi_probe (struct device*) ; 
 int /*<<< orphan*/  fimd_component_ops ; 
 int /*<<< orphan*/  fimd_irq_handler ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fimd_context*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/ * syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int fimd_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct fimd_context *ctx;
	struct device_node *i80_if_timings;
	struct resource *res;
	int ret;

	if (!dev->of_node)
		return -ENODEV;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev = dev;
	ctx->suspended = true;
	ctx->driver_data = of_device_get_match_data(dev);

	if (of_property_read_bool(dev->of_node, "samsung,invert-vden"))
		ctx->vidcon1 |= VIDCON1_INV_VDEN;
	if (of_property_read_bool(dev->of_node, "samsung,invert-vclk"))
		ctx->vidcon1 |= VIDCON1_INV_VCLK;

	i80_if_timings = of_get_child_by_name(dev->of_node, "i80-if-timings");
	if (i80_if_timings) {
		u32 val;

		ctx->i80_if = true;

		if (ctx->driver_data->has_vidoutcon)
			ctx->vidout_con |= VIDOUT_CON_F_I80_LDI0;
		else
			ctx->vidcon0 |= VIDCON0_VIDOUT_I80_LDI0;
		/*
		 * The user manual describes that this "DSI_EN" bit is required
		 * to enable I80 24-bit data interface.
		 */
		ctx->vidcon0 |= VIDCON0_DSI_EN;

		if (of_property_read_u32(i80_if_timings, "cs-setup", &val))
			val = 0;
		ctx->i80ifcon = LCD_CS_SETUP(val);
		if (of_property_read_u32(i80_if_timings, "wr-setup", &val))
			val = 0;
		ctx->i80ifcon |= LCD_WR_SETUP(val);
		if (of_property_read_u32(i80_if_timings, "wr-active", &val))
			val = 1;
		ctx->i80ifcon |= LCD_WR_ACTIVE(val);
		if (of_property_read_u32(i80_if_timings, "wr-hold", &val))
			val = 0;
		ctx->i80ifcon |= LCD_WR_HOLD(val);
	}
	of_node_put(i80_if_timings);

	ctx->sysreg = syscon_regmap_lookup_by_phandle(dev->of_node,
							"samsung,sysreg");
	if (IS_ERR(ctx->sysreg)) {
		dev_warn(dev, "failed to get system register.\n");
		ctx->sysreg = NULL;
	}

	ctx->bus_clk = devm_clk_get(dev, "fimd");
	if (IS_ERR(ctx->bus_clk)) {
		dev_err(dev, "failed to get bus clock\n");
		return PTR_ERR(ctx->bus_clk);
	}

	ctx->lcd_clk = devm_clk_get(dev, "sclk_fimd");
	if (IS_ERR(ctx->lcd_clk)) {
		dev_err(dev, "failed to get lcd clock\n");
		return PTR_ERR(ctx->lcd_clk);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	ctx->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(ctx->regs))
		return PTR_ERR(ctx->regs);

	res = platform_get_resource_byname(pdev, IORESOURCE_IRQ,
					   ctx->i80_if ? "lcd_sys" : "vsync");
	if (!res) {
		dev_err(dev, "irq request failed.\n");
		return -ENXIO;
	}

	ret = devm_request_irq(dev, res->start, fimd_irq_handler,
							0, "drm_fimd", ctx);
	if (ret) {
		dev_err(dev, "irq request failed.\n");
		return ret;
	}

	init_waitqueue_head(&ctx->wait_vsync_queue);
	atomic_set(&ctx->wait_vsync_event, 0);

	platform_set_drvdata(pdev, ctx);

	ctx->encoder = exynos_dpi_probe(dev);
	if (IS_ERR(ctx->encoder))
		return PTR_ERR(ctx->encoder);

	pm_runtime_enable(dev);

	ret = component_add(dev, &fimd_component_ops);
	if (ret)
		goto err_disable_pm_runtime;

	return ret;

err_disable_pm_runtime:
	pm_runtime_disable(dev);

	return ret;
}