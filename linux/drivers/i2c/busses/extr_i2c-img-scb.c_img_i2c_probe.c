#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int dummy; } ;
struct TYPE_21__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_19__ {struct device_node* of_node; TYPE_3__* parent; } ;
struct TYPE_18__ {int retries; int /*<<< orphan*/  name; int /*<<< orphan*/  nr; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; TYPE_1__ dev; } ;
struct img_i2c {TYPE_11__ adap; int /*<<< orphan*/  msg_complete; int /*<<< orphan*/  lock; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  check_timer; void* scb_clk; void* sys_clk; void* base; } ;
struct device_node {int dummy; } ;
struct TYPE_20__ {int /*<<< orphan*/  max_bitrate; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMG_I2C_PM_TIMEOUT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MODE_INACTIVE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 void* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct img_i2c* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct img_i2c*) ; 
 int i2c_add_numbered_adapter (TYPE_11__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_11__*,struct img_i2c*) ; 
 int /*<<< orphan*/  img_i2c_algo ; 
 int /*<<< orphan*/  img_i2c_check_timer ; 
 int img_i2c_init (struct img_i2c*) ; 
 int /*<<< orphan*/  img_i2c_isr ; 
 int img_i2c_runtime_resume (TYPE_3__*) ; 
 int /*<<< orphan*/  img_i2c_runtime_suspend (TYPE_3__*) ; 
 int /*<<< orphan*/  img_i2c_switch_mode (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct img_i2c*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_3__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* timings ; 

__attribute__((used)) static int img_i2c_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct img_i2c *i2c;
	struct resource *res;
	int irq, ret;
	u32 val;

	i2c = devm_kzalloc(&pdev->dev, sizeof(struct img_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c->base))
		return PTR_ERR(i2c->base);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "can't get irq number\n");
		return irq;
	}

	i2c->sys_clk = devm_clk_get(&pdev->dev, "sys");
	if (IS_ERR(i2c->sys_clk)) {
		dev_err(&pdev->dev, "can't get system clock\n");
		return PTR_ERR(i2c->sys_clk);
	}

	i2c->scb_clk = devm_clk_get(&pdev->dev, "scb");
	if (IS_ERR(i2c->scb_clk)) {
		dev_err(&pdev->dev, "can't get core clock\n");
		return PTR_ERR(i2c->scb_clk);
	}

	ret = devm_request_irq(&pdev->dev, irq, img_i2c_isr, 0,
			       pdev->name, i2c);
	if (ret) {
		dev_err(&pdev->dev, "can't request irq %d\n", irq);
		return ret;
	}

	/* Set up the exception check timer */
	timer_setup(&i2c->check_timer, img_i2c_check_timer, 0);

	i2c->bitrate = timings[0].max_bitrate;
	if (!of_property_read_u32(node, "clock-frequency", &val))
		i2c->bitrate = val;

	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = node;
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &img_i2c_algo;
	i2c->adap.retries = 5;
	i2c->adap.nr = pdev->id;
	snprintf(i2c->adap.name, sizeof(i2c->adap.name), "IMG SCB I2C");

	img_i2c_switch_mode(i2c, MODE_INACTIVE);
	spin_lock_init(&i2c->lock);
	init_completion(&i2c->msg_complete);

	platform_set_drvdata(pdev, i2c);

	pm_runtime_set_autosuspend_delay(&pdev->dev, IMG_I2C_PM_TIMEOUT);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	if (!pm_runtime_enabled(&pdev->dev)) {
		ret = img_i2c_runtime_resume(&pdev->dev);
		if (ret)
			return ret;
	}

	ret = img_i2c_init(i2c);
	if (ret)
		goto rpm_disable;

	ret = i2c_add_numbered_adapter(&i2c->adap);
	if (ret < 0)
		goto rpm_disable;

	return 0;

rpm_disable:
	if (!pm_runtime_enabled(&pdev->dev))
		img_i2c_runtime_suspend(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	pm_runtime_dont_use_autosuspend(&pdev->dev);
	return ret;
}