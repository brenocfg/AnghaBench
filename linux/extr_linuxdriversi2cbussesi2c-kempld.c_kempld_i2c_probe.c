#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_7__ {TYPE_5__* parent; } ;
struct TYPE_8__ {int nr; TYPE_1__ dev; } ;
struct kempld_i2c_data {int was_active; TYPE_5__* dev; TYPE_2__ adap; struct kempld_device_data* pld; } ;
struct kempld_device_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_CTRL_EN ; 
 int /*<<< orphan*/  KEMPLD_I2C_CTRL ; 
 int /*<<< orphan*/  bus_frequency ; 
 struct kempld_device_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 struct kempld_i2c_data* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int i2c_add_numbered_adapter (TYPE_2__*) ; 
 int i2c_bus ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct kempld_i2c_data*) ; 
 int /*<<< orphan*/  kempld_get_mutex (struct kempld_device_data*) ; 
 TYPE_2__ kempld_i2c_adapter ; 
 int /*<<< orphan*/  kempld_i2c_device_init (struct kempld_i2c_data*) ; 
 int kempld_read8 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_release_mutex (struct kempld_device_data*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct kempld_i2c_data*) ; 

__attribute__((used)) static int kempld_i2c_probe(struct platform_device *pdev)
{
	struct kempld_device_data *pld = dev_get_drvdata(pdev->dev.parent);
	struct kempld_i2c_data *i2c;
	int ret;
	u8 ctrl;

	i2c = devm_kzalloc(&pdev->dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	i2c->pld = pld;
	i2c->dev = &pdev->dev;
	i2c->adap = kempld_i2c_adapter;
	i2c->adap.dev.parent = i2c->dev;
	i2c_set_adapdata(&i2c->adap, i2c);
	platform_set_drvdata(pdev, i2c);

	kempld_get_mutex(pld);
	ctrl = kempld_read8(pld, KEMPLD_I2C_CTRL);

	if (ctrl & I2C_CTRL_EN)
		i2c->was_active = true;

	kempld_i2c_device_init(i2c);
	kempld_release_mutex(pld);

	/* Add I2C adapter to I2C tree */
	if (i2c_bus >= -1)
		i2c->adap.nr = i2c_bus;
	ret = i2c_add_numbered_adapter(&i2c->adap);
	if (ret)
		return ret;

	dev_info(i2c->dev, "I2C bus initialized at %dkHz\n",
		 bus_frequency);

	return 0;
}