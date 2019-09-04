#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_4__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; TYPE_4__* parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  nr; TYPE_1__ dev; TYPE_2__* algo_data; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;
struct TYPE_7__ {struct i2c_versatile* data; } ;
struct i2c_versatile {TYPE_3__ adap; TYPE_2__ algo; scalar_t__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ I2C_CONTROLS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int SCL ; 
 int SDA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct i2c_versatile* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int i2c_bit_add_numbered_bus (TYPE_3__*) ; 
 TYPE_2__ i2c_versatile_algo ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct i2c_versatile*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int i2c_versatile_probe(struct platform_device *dev)
{
	struct i2c_versatile *i2c;
	struct resource *r;
	int ret;

	i2c = devm_kzalloc(&dev->dev, sizeof(struct i2c_versatile), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	r = platform_get_resource(dev, IORESOURCE_MEM, 0);
	i2c->base = devm_ioremap_resource(&dev->dev, r);
	if (IS_ERR(i2c->base))
		return PTR_ERR(i2c->base);

	writel(SCL | SDA, i2c->base + I2C_CONTROLS);

	i2c->adap.owner = THIS_MODULE;
	strlcpy(i2c->adap.name, "Versatile I2C adapter", sizeof(i2c->adap.name));
	i2c->adap.algo_data = &i2c->algo;
	i2c->adap.dev.parent = &dev->dev;
	i2c->adap.dev.of_node = dev->dev.of_node;
	i2c->algo = i2c_versatile_algo;
	i2c->algo.data = i2c;

	i2c->adap.nr = dev->id;
	ret = i2c_bit_add_numbered_bus(&i2c->adap);
	if (ret < 0)
		return ret;

	platform_set_drvdata(dev, i2c);

	return 0;
}