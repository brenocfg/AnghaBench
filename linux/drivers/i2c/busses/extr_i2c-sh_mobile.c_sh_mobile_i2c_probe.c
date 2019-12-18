#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int retries; int /*<<< orphan*/  nr; int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/ * quirks; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct sh_mobile_i2c_data {int clks_per_count; int /*<<< orphan*/  bus_speed; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; struct i2c_adapter adap; int /*<<< orphan*/  dma_tx; int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_direction; int /*<<< orphan*/  sg; int /*<<< orphan*/  flags; int /*<<< orphan*/  reg; struct resource* res; TYPE_2__* dev; int /*<<< orphan*/  clk; } ;
struct sh_mobile_dt_config {int clks_per_count; int (* setup ) (struct sh_mobile_i2c_data*) ;} ;
struct resource {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IIC_FLAG_HAS_ICIC67 ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STANDARD_MODE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct sh_mobile_i2c_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct sh_mobile_dt_config* of_device_get_match_data (TYPE_2__*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_2__*) ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sh_mobile_i2c_algorithm ; 
 int sh_mobile_i2c_hook_irqs (struct platform_device*,struct sh_mobile_i2c_data*) ; 
 int sh_mobile_i2c_init (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  sh_mobile_i2c_quirks ; 
 int /*<<< orphan*/  sh_mobile_i2c_release_dma (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct sh_mobile_i2c_data*) ; 

__attribute__((used)) static int sh_mobile_i2c_probe(struct platform_device *dev)
{
	struct sh_mobile_i2c_data *pd;
	struct i2c_adapter *adap;
	struct resource *res;
	const struct sh_mobile_dt_config *config;
	int ret;
	u32 bus_speed;

	pd = devm_kzalloc(&dev->dev, sizeof(struct sh_mobile_i2c_data), GFP_KERNEL);
	if (!pd)
		return -ENOMEM;

	pd->clk = devm_clk_get(&dev->dev, NULL);
	if (IS_ERR(pd->clk)) {
		dev_err(&dev->dev, "cannot get clock\n");
		return PTR_ERR(pd->clk);
	}

	ret = sh_mobile_i2c_hook_irqs(dev, pd);
	if (ret)
		return ret;

	pd->dev = &dev->dev;
	platform_set_drvdata(dev, pd);

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);

	pd->res = res;
	pd->reg = devm_ioremap_resource(&dev->dev, res);
	if (IS_ERR(pd->reg))
		return PTR_ERR(pd->reg);

	ret = of_property_read_u32(dev->dev.of_node, "clock-frequency", &bus_speed);
	pd->bus_speed = (ret || !bus_speed) ? STANDARD_MODE : bus_speed;
	pd->clks_per_count = 1;

	/* Newer variants come with two new bits in ICIC */
	if (resource_size(res) > 0x17)
		pd->flags |= IIC_FLAG_HAS_ICIC67;

	pm_runtime_enable(&dev->dev);
	pm_runtime_get_sync(&dev->dev);

	config = of_device_get_match_data(&dev->dev);
	if (config) {
		pd->clks_per_count = config->clks_per_count;
		ret = config->setup(pd);
	} else {
		ret = sh_mobile_i2c_init(pd);
	}

	pm_runtime_put_sync(&dev->dev);
	if (ret)
		return ret;

	/* Init DMA */
	sg_init_table(&pd->sg, 1);
	pd->dma_direction = DMA_NONE;
	pd->dma_rx = pd->dma_tx = ERR_PTR(-EPROBE_DEFER);

	/* setup the private data */
	adap = &pd->adap;
	i2c_set_adapdata(adap, pd);

	adap->owner = THIS_MODULE;
	adap->algo = &sh_mobile_i2c_algorithm;
	adap->quirks = &sh_mobile_i2c_quirks;
	adap->dev.parent = &dev->dev;
	adap->retries = 5;
	adap->nr = dev->id;
	adap->dev.of_node = dev->dev.of_node;

	strlcpy(adap->name, dev->name, sizeof(adap->name));

	spin_lock_init(&pd->lock);
	init_waitqueue_head(&pd->wait);

	ret = i2c_add_numbered_adapter(adap);
	if (ret < 0) {
		sh_mobile_i2c_release_dma(pd);
		return ret;
	}

	dev_info(&dev->dev, "I2C adapter %d, bus speed %lu Hz\n", adap->nr, pd->bus_speed);

	return 0;
}