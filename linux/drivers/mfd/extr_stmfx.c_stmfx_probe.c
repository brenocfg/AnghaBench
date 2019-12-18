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
struct stmfx {int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  lock; int /*<<< orphan*/  map; struct device* dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int irq; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct stmfx* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct stmfx*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmfx_cells ; 
 int /*<<< orphan*/  stmfx_chip_exit (struct i2c_client*) ; 
 int stmfx_chip_init (struct i2c_client*) ; 
 int /*<<< orphan*/  stmfx_irq_exit (struct i2c_client*) ; 
 int stmfx_irq_init (struct i2c_client*) ; 
 int /*<<< orphan*/  stmfx_regmap_config ; 

__attribute__((used)) static int stmfx_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct stmfx *stmfx;
	int ret;

	stmfx = devm_kzalloc(dev, sizeof(*stmfx), GFP_KERNEL);
	if (!stmfx)
		return -ENOMEM;

	i2c_set_clientdata(client, stmfx);

	stmfx->dev = dev;

	stmfx->map = devm_regmap_init_i2c(client, &stmfx_regmap_config);
	if (IS_ERR(stmfx->map)) {
		ret = PTR_ERR(stmfx->map);
		dev_err(dev, "Failed to allocate register map: %d\n", ret);
		return ret;
	}

	mutex_init(&stmfx->lock);

	ret = stmfx_chip_init(client);
	if (ret) {
		if (ret == -ETIMEDOUT)
			return -EPROBE_DEFER;
		return ret;
	}

	if (client->irq < 0) {
		dev_err(dev, "Failed to get IRQ: %d\n", client->irq);
		ret = client->irq;
		goto err_chip_exit;
	}

	ret = stmfx_irq_init(client);
	if (ret)
		goto err_chip_exit;

	ret = devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				   stmfx_cells, ARRAY_SIZE(stmfx_cells), NULL,
				   0, stmfx->irq_domain);
	if (ret)
		goto err_irq_exit;

	return 0;

err_irq_exit:
	stmfx_irq_exit(client);
err_chip_exit:
	stmfx_chip_exit(client);

	return ret;
}