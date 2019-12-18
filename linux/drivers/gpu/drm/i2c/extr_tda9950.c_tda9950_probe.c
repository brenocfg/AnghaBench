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
typedef  int u8 ;
struct tda9950_priv {int /*<<< orphan*/  notify; int /*<<< orphan*/  adap; struct device* hdmi; struct tda9950_glue* glue; struct i2c_client* client; } ;
struct tda9950_glue {unsigned long irq_flags; struct device* parent; } ;
struct i2c_device_id {int dummy; } ;
struct device {struct tda9950_glue* platform_data; } ;
struct i2c_client {struct device dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_CAP_DEFAULTS ; 
 int /*<<< orphan*/  CEC_MAX_LOG_ADDRS ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_SHARED ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CVR ; 
 int /*<<< orphan*/  cec_allocate_adapter (int /*<<< orphan*/ *,struct tda9950_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_delete_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_notifier_get (struct device*) ; 
 int /*<<< orphan*/  cec_notifier_put (int /*<<< orphan*/ ) ; 
 int cec_register_adapter (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  cec_register_cec_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_add_action (struct device*,int /*<<< orphan*/ ,struct tda9950_priv*) ; 
 struct tda9950_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_remove_action (struct device*,int /*<<< orphan*/ ,struct tda9950_priv*) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct tda9950_priv*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tda9950_priv*) ; 
 int /*<<< orphan*/  tda9950_cec_del ; 
 int /*<<< orphan*/  tda9950_cec_ops ; 
 int tda9950_devm_glue_init (struct device*,struct tda9950_glue*) ; 
 int tda9950_glue_open (struct tda9950_priv*) ; 
 int /*<<< orphan*/  tda9950_glue_release (struct tda9950_priv*) ; 
 int /*<<< orphan*/  tda9950_irq ; 
 int tda9950_read (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda9950_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct tda9950_glue *glue = client->dev.platform_data;
	struct device *dev = &client->dev;
	struct tda9950_priv *priv;
	unsigned long irqflags;
	int ret;
	u8 cvr;

	/*
	 * We must have I2C functionality: our multi-byte accesses
	 * must be performed as a single contiguous transaction.
	 */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev,
			"adapter does not support I2C functionality\n");
		return -ENXIO;
	}

	/* We must have an interrupt to be functional. */
	if (client->irq <= 0) {
		dev_err(&client->dev, "driver requires an interrupt\n");
		return -ENXIO;
	}

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->client = client;
	priv->glue = glue;

	i2c_set_clientdata(client, priv);

	/*
	 * If we're part of a TDA998x, we want the class devices to be
	 * associated with the HDMI Tx so we have a tight relationship
	 * between the HDMI interface and the CEC interface.
	 */
	priv->hdmi = dev;
	if (glue && glue->parent)
		priv->hdmi = glue->parent;

	priv->adap = cec_allocate_adapter(&tda9950_cec_ops, priv, "tda9950",
					  CEC_CAP_DEFAULTS,
					  CEC_MAX_LOG_ADDRS);
	if (IS_ERR(priv->adap))
		return PTR_ERR(priv->adap);

	ret = devm_add_action(dev, tda9950_cec_del, priv);
	if (ret) {
		cec_delete_adapter(priv->adap);
		return ret;
	}

	ret = tda9950_devm_glue_init(dev, glue);
	if (ret)
		return ret;

	ret = tda9950_glue_open(priv);
	if (ret)
		return ret;

	cvr = tda9950_read(client, REG_CVR);

	dev_info(&client->dev,
		 "TDA9950 CEC interface, hardware version %u.%u\n",
		 cvr >> 4, cvr & 15);

	tda9950_glue_release(priv);

	irqflags = IRQF_TRIGGER_FALLING;
	if (glue)
		irqflags = glue->irq_flags;

	ret = devm_request_threaded_irq(dev, client->irq, NULL, tda9950_irq,
					irqflags | IRQF_SHARED | IRQF_ONESHOT,
					dev_name(&client->dev), priv);
	if (ret < 0)
		return ret;

	priv->notify = cec_notifier_get(priv->hdmi);
	if (!priv->notify)
		return -ENOMEM;

	ret = cec_register_adapter(priv->adap, priv->hdmi);
	if (ret < 0) {
		cec_notifier_put(priv->notify);
		return ret;
	}

	/*
	 * CEC documentation says we must not call cec_delete_adapter
	 * after a successful call to cec_register_adapter().
	 */
	devm_remove_action(dev, tda9950_cec_del, priv);

	cec_register_cec_notifier(priv->adap, priv->notify);

	return 0;
}