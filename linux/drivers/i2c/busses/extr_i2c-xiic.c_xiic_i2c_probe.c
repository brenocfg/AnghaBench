#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct xiic_i2c_platform_data {scalar_t__ num_devices; scalar_t__ devices; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; TYPE_3__* parent; } ;
struct TYPE_19__ {TYPE_1__ dev; } ;
struct xiic_i2c {int /*<<< orphan*/  clk; TYPE_2__ adap; int /*<<< orphan*/  endianness; TYPE_3__* dev; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct TYPE_20__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LITTLE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XIIC_CR_REG_OFFSET ; 
 int /*<<< orphan*/  XIIC_CR_TX_FIFO_RESET_MASK ; 
 int /*<<< orphan*/  XIIC_PM_TIMEOUT ; 
 int /*<<< orphan*/  XIIC_SR_REG_OFFSET ; 
 int XIIC_SR_TX_FIFO_EMPTY_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct xiic_i2c_platform_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct xiic_i2c* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xiic_i2c*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_new_device (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct xiic_i2c*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xiic_i2c*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_3__*) ; 
 TYPE_2__ xiic_adapter ; 
 int /*<<< orphan*/  xiic_deinit (struct xiic_i2c*) ; 
 int xiic_getreg32 (struct xiic_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xiic_isr ; 
 int /*<<< orphan*/  xiic_process ; 
 int /*<<< orphan*/  xiic_reinit (struct xiic_i2c*) ; 
 int /*<<< orphan*/  xiic_setreg32 (struct xiic_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xiic_i2c_probe(struct platform_device *pdev)
{
	struct xiic_i2c *i2c;
	struct xiic_i2c_platform_data *pdata;
	struct resource *res;
	int ret, irq;
	u8 i;
	u32 sr;

	i2c = devm_kzalloc(&pdev->dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c->base))
		return PTR_ERR(i2c->base);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	pdata = dev_get_platdata(&pdev->dev);

	/* hook up driver to tree */
	platform_set_drvdata(pdev, i2c);
	i2c->adap = xiic_adapter;
	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	mutex_init(&i2c->lock);
	init_waitqueue_head(&i2c->wait);

	i2c->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(i2c->clk)) {
		dev_err(&pdev->dev, "input clock not found.\n");
		return PTR_ERR(i2c->clk);
	}
	ret = clk_prepare_enable(i2c->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		return ret;
	}
	i2c->dev = &pdev->dev;
	pm_runtime_enable(i2c->dev);
	pm_runtime_set_autosuspend_delay(i2c->dev, XIIC_PM_TIMEOUT);
	pm_runtime_use_autosuspend(i2c->dev);
	pm_runtime_set_active(i2c->dev);
	ret = devm_request_threaded_irq(&pdev->dev, irq, xiic_isr,
					xiic_process, IRQF_ONESHOT,
					pdev->name, i2c);

	if (ret < 0) {
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		goto err_clk_dis;
	}

	/*
	 * Detect endianness
	 * Try to reset the TX FIFO. Then check the EMPTY flag. If it is not
	 * set, assume that the endianness was wrong and swap.
	 */
	i2c->endianness = LITTLE;
	xiic_setreg32(i2c, XIIC_CR_REG_OFFSET, XIIC_CR_TX_FIFO_RESET_MASK);
	/* Reset is cleared in xiic_reinit */
	sr = xiic_getreg32(i2c, XIIC_SR_REG_OFFSET);
	if (!(sr & XIIC_SR_TX_FIFO_EMPTY_MASK))
		i2c->endianness = BIG;

	xiic_reinit(i2c);

	/* add i2c adapter to i2c tree */
	ret = i2c_add_adapter(&i2c->adap);
	if (ret) {
		xiic_deinit(i2c);
		goto err_clk_dis;
	}

	if (pdata) {
		/* add in known devices to the bus */
		for (i = 0; i < pdata->num_devices; i++)
			i2c_new_device(&i2c->adap, pdata->devices + i);
	}

	return 0;

err_clk_dis:
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(i2c->clk);
	return ret;
}