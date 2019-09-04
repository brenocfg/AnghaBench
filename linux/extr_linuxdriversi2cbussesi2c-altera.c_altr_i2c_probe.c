#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct resource {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; TYPE_4__* parent; } ;
struct TYPE_12__ {TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct altr_i2c_dev {int fifo_size; int bus_clk_rate; int /*<<< orphan*/  i2c_clk; TYPE_2__ adapter; TYPE_4__* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_complete; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ALTR_I2C_DFLT_FIFO_SZ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  altr_i2c_algo ; 
 int /*<<< orphan*/  altr_i2c_init (struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  altr_i2c_isr ; 
 int /*<<< orphan*/  altr_i2c_isr_quick ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*) ; 
 scalar_t__ device_property_read_u32 (TYPE_4__*,char*,int*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct altr_i2c_dev* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct altr_i2c_dev*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct altr_i2c_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int altr_i2c_probe(struct platform_device *pdev)
{
	struct altr_i2c_dev *idev = NULL;
	struct resource *res;
	int irq, ret;
	u32 val;

	idev = devm_kzalloc(&pdev->dev, sizeof(*idev), GFP_KERNEL);
	if (!idev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	idev->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(idev->base))
		return PTR_ERR(idev->base);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "missing interrupt resource\n");
		return irq;
	}

	idev->i2c_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(idev->i2c_clk)) {
		dev_err(&pdev->dev, "missing clock\n");
		return PTR_ERR(idev->i2c_clk);
	}

	idev->dev = &pdev->dev;
	init_completion(&idev->msg_complete);
	spin_lock_init(&idev->lock);

	val = device_property_read_u32(idev->dev, "fifo-size",
				       &idev->fifo_size);
	if (val) {
		dev_err(&pdev->dev, "FIFO size set to default of %d\n",
			ALTR_I2C_DFLT_FIFO_SZ);
		idev->fifo_size = ALTR_I2C_DFLT_FIFO_SZ;
	}

	val = device_property_read_u32(idev->dev, "clock-frequency",
				       &idev->bus_clk_rate);
	if (val) {
		dev_err(&pdev->dev, "Default to 100kHz\n");
		idev->bus_clk_rate = 100000;	/* default clock rate */
	}

	if (idev->bus_clk_rate > 400000) {
		dev_err(&pdev->dev, "invalid clock-frequency %d\n",
			idev->bus_clk_rate);
		return -EINVAL;
	}

	ret = devm_request_threaded_irq(&pdev->dev, irq, altr_i2c_isr_quick,
					altr_i2c_isr, IRQF_ONESHOT,
					pdev->name, idev);
	if (ret) {
		dev_err(&pdev->dev, "failed to claim IRQ %d\n", irq);
		return ret;
	}

	ret = clk_prepare_enable(idev->i2c_clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable clock\n");
		return ret;
	}

	altr_i2c_init(idev);

	i2c_set_adapdata(&idev->adapter, idev);
	strlcpy(idev->adapter.name, pdev->name, sizeof(idev->adapter.name));
	idev->adapter.owner = THIS_MODULE;
	idev->adapter.algo = &altr_i2c_algo;
	idev->adapter.dev.parent = &pdev->dev;
	idev->adapter.dev.of_node = pdev->dev.of_node;

	platform_set_drvdata(pdev, idev);

	ret = i2c_add_adapter(&idev->adapter);
	if (ret) {
		clk_disable_unprepare(idev->i2c_clk);
		return ret;
	}
	dev_info(&pdev->dev, "Altera SoftIP I2C Probe Complete\n");

	return 0;
}