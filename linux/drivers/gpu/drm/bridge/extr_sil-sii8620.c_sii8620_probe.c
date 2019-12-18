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
struct TYPE_3__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct sii8620 {int /*<<< orphan*/  extcon; TYPE_1__ bridge; struct device* dev; TYPE_2__* supplies; int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  clk_xtal; int /*<<< orphan*/  mt_queue; int /*<<< orphan*/  lock; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;
struct TYPE_4__ {char* supply; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct sii8620* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_2__*) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct sii8620*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sii8620*) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sii8620_bridge_funcs ; 
 int /*<<< orphan*/  sii8620_cable_in (struct sii8620*) ; 
 int sii8620_extcon_init (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_irq_thread ; 

__attribute__((used)) static int sii8620_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct sii8620 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev = dev;
	mutex_init(&ctx->lock);
	INIT_LIST_HEAD(&ctx->mt_queue);

	ctx->clk_xtal = devm_clk_get(dev, "xtal");
	if (IS_ERR(ctx->clk_xtal)) {
		dev_err(dev, "failed to get xtal clock from DT\n");
		return PTR_ERR(ctx->clk_xtal);
	}

	if (!client->irq) {
		dev_err(dev, "no irq provided\n");
		return -EINVAL;
	}
	irq_set_status_flags(client->irq, IRQ_NOAUTOEN);
	ret = devm_request_threaded_irq(dev, client->irq, NULL,
					sii8620_irq_thread,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"sii8620", ctx);
	if (ret < 0) {
		dev_err(dev, "failed to install IRQ handler\n");
		return ret;
	}

	ctx->gpio_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->gpio_reset)) {
		dev_err(dev, "failed to get reset gpio from DT\n");
		return PTR_ERR(ctx->gpio_reset);
	}

	ctx->supplies[0].supply = "cvcc10";
	ctx->supplies[1].supply = "iovcc18";
	ret = devm_regulator_bulk_get(dev, 2, ctx->supplies);
	if (ret)
		return ret;

	ret = sii8620_extcon_init(ctx);
	if (ret < 0) {
		dev_err(ctx->dev, "failed to initialize EXTCON\n");
		return ret;
	}

	i2c_set_clientdata(client, ctx);

	ctx->bridge.funcs = &sii8620_bridge_funcs;
	ctx->bridge.of_node = dev->of_node;
	drm_bridge_add(&ctx->bridge);

	if (!ctx->extcon)
		sii8620_cable_in(ctx);

	return 0;
}