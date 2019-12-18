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
struct TYPE_2__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct sii9234 {TYPE_1__ bridge; int /*<<< orphan*/  lock; struct device* dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sii9234* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct sii9234*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sii9234*) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sii9234_bridge_funcs ; 
 int /*<<< orphan*/  sii9234_cable_in (struct sii9234*) ; 
 int sii9234_init_resources (struct sii9234*,struct i2c_client*) ; 
 int /*<<< orphan*/  sii9234_irq_thread ; 

__attribute__((used)) static int sii9234_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct sii9234 *ctx;
	struct device *dev = &client->dev;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev = dev;
	mutex_init(&ctx->lock);

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(dev, "I2C adapter lacks SMBUS feature\n");
		return -EIO;
	}

	if (!client->irq) {
		dev_err(dev, "no irq provided\n");
		return -EINVAL;
	}

	irq_set_status_flags(client->irq, IRQ_NOAUTOEN);
	ret = devm_request_threaded_irq(dev, client->irq, NULL,
					sii9234_irq_thread,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"sii9234", ctx);
	if (ret < 0) {
		dev_err(dev, "failed to install IRQ handler\n");
		return ret;
	}

	ret = sii9234_init_resources(ctx, client);
	if (ret < 0)
		return ret;

	i2c_set_clientdata(client, ctx);

	ctx->bridge.funcs = &sii9234_bridge_funcs;
	ctx->bridge.of_node = dev->of_node;
	drm_bridge_add(&ctx->bridge);

	sii9234_cable_in(ctx);

	return 0;
}