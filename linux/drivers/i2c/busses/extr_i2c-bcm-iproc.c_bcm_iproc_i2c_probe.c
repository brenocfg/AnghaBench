#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct i2c_adapter {TYPE_1__ dev; int /*<<< orphan*/ * quirks; TYPE_8__* algo; int /*<<< orphan*/  name; } ;
struct bcm_iproc_i2c_dev {int type; int irq; TYPE_2__* device; struct i2c_adapter adapter; int /*<<< orphan*/  idm_lock; int /*<<< orphan*/  ape_addr_mask; void* idm_base; void* base; int /*<<< orphan*/  done; } ;
typedef  enum bcm_iproc_i2c_type { ____Placeholder_bcm_iproc_i2c_type } bcm_iproc_i2c_type ;
struct TYPE_11__ {int /*<<< orphan*/ * unreg_slave; int /*<<< orphan*/ * reg_slave; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IPROC_I2C_NIC ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 TYPE_8__ bcm_iproc_algo ; 
 int bcm_iproc_i2c_cfg_speed (struct bcm_iproc_i2c_dev*) ; 
 int /*<<< orphan*/  bcm_iproc_i2c_enable_disable (struct bcm_iproc_i2c_dev*,int) ; 
 int bcm_iproc_i2c_init (struct bcm_iproc_i2c_dev*) ; 
 int /*<<< orphan*/  bcm_iproc_i2c_isr ; 
 int /*<<< orphan*/  bcm_iproc_i2c_quirks ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 void* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct bcm_iproc_i2c_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcm_iproc_i2c_dev*) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct bcm_iproc_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (TYPE_2__*) ; 
 char* of_node_full_name (int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm_iproc_i2c_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm_iproc_i2c_probe(struct platform_device *pdev)
{
	int irq, ret = 0;
	struct bcm_iproc_i2c_dev *iproc_i2c;
	struct i2c_adapter *adap;
	struct resource *res;

	iproc_i2c = devm_kzalloc(&pdev->dev, sizeof(*iproc_i2c),
				 GFP_KERNEL);
	if (!iproc_i2c)
		return -ENOMEM;

	platform_set_drvdata(pdev, iproc_i2c);
	iproc_i2c->device = &pdev->dev;
	iproc_i2c->type =
		(enum bcm_iproc_i2c_type)of_device_get_match_data(&pdev->dev);
	init_completion(&iproc_i2c->done);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	iproc_i2c->base = devm_ioremap_resource(iproc_i2c->device, res);
	if (IS_ERR(iproc_i2c->base))
		return PTR_ERR(iproc_i2c->base);

	if (iproc_i2c->type == IPROC_I2C_NIC) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
		iproc_i2c->idm_base = devm_ioremap_resource(iproc_i2c->device,
							    res);
		if (IS_ERR(iproc_i2c->idm_base))
			return PTR_ERR(iproc_i2c->idm_base);

		ret = of_property_read_u32(iproc_i2c->device->of_node,
					   "brcm,ape-hsls-addr-mask",
					   &iproc_i2c->ape_addr_mask);
		if (ret < 0) {
			dev_err(iproc_i2c->device,
				"'brcm,ape-hsls-addr-mask' missing\n");
			return -EINVAL;
		}

		spin_lock_init(&iproc_i2c->idm_lock);

		/* no slave support */
		bcm_iproc_algo.reg_slave = NULL;
		bcm_iproc_algo.unreg_slave = NULL;
	}

	ret = bcm_iproc_i2c_init(iproc_i2c);
	if (ret)
		return ret;

	ret = bcm_iproc_i2c_cfg_speed(iproc_i2c);
	if (ret)
		return ret;

	irq = platform_get_irq(pdev, 0);
	if (irq > 0) {
		ret = devm_request_irq(iproc_i2c->device, irq,
				       bcm_iproc_i2c_isr, 0, pdev->name,
				       iproc_i2c);
		if (ret < 0) {
			dev_err(iproc_i2c->device,
				"unable to request irq %i\n", irq);
			return ret;
		}

		iproc_i2c->irq = irq;
	} else {
		dev_warn(iproc_i2c->device,
			 "no irq resource, falling back to poll mode\n");
	}

	bcm_iproc_i2c_enable_disable(iproc_i2c, true);

	adap = &iproc_i2c->adapter;
	i2c_set_adapdata(adap, iproc_i2c);
	snprintf(adap->name, sizeof(adap->name),
		"Broadcom iProc (%s)",
		of_node_full_name(iproc_i2c->device->of_node));
	adap->algo = &bcm_iproc_algo;
	adap->quirks = &bcm_iproc_i2c_quirks;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	return i2c_add_adapter(adap);
}