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
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_13__ {scalar_t__ of_node; } ;
struct platform_device {char* name; TYPE_4__ dev; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; TYPE_4__* parent; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/  nr; struct i2c_pnx_algo_data* algo_data; int /*<<< orphan*/ * algo; } ;
struct TYPE_11__ {int /*<<< orphan*/  complete; int /*<<< orphan*/  timer; } ;
struct i2c_pnx_algo_data {int irq; int /*<<< orphan*/  clk; TYPE_3__ adapter; TYPE_2__ mif; int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_PNX_SPEED_KHZ_DEFAULT ; 
 int /*<<< orphan*/  I2C_PNX_TIMEOUT_DEFAULT ; 
 int /*<<< orphan*/  I2C_REG_CKH (struct i2c_pnx_algo_data*) ; 
 int /*<<< orphan*/  I2C_REG_CKL (struct i2c_pnx_algo_data*) ; 
 int /*<<< orphan*/  I2C_REG_CTL (struct i2c_pnx_algo_data*) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct i2c_pnx_algo_data* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct i2c_pnx_algo_data*) ; 
 int i2c_add_numbered_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_pnx_interrupt ; 
 int /*<<< orphan*/  i2c_pnx_timeout ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long mcntrl_reset ; 
 int /*<<< orphan*/  of_node_get (scalar_t__) ; 
 int /*<<< orphan*/  of_property_read_u32 (scalar_t__,char*,unsigned long*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct i2c_pnx_algo_data*) ; 
 int /*<<< orphan*/  pnx_algorithm ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_reset (struct i2c_pnx_algo_data*) ; 

__attribute__((used)) static int i2c_pnx_probe(struct platform_device *pdev)
{
	unsigned long tmp;
	int ret = 0;
	struct i2c_pnx_algo_data *alg_data;
	unsigned long freq;
	struct resource *res;
	u32 speed = I2C_PNX_SPEED_KHZ_DEFAULT * 1000;

	alg_data = devm_kzalloc(&pdev->dev, sizeof(*alg_data), GFP_KERNEL);
	if (!alg_data)
		return -ENOMEM;

	platform_set_drvdata(pdev, alg_data);

	alg_data->adapter.dev.parent = &pdev->dev;
	alg_data->adapter.algo = &pnx_algorithm;
	alg_data->adapter.algo_data = alg_data;
	alg_data->adapter.nr = pdev->id;

	alg_data->timeout = I2C_PNX_TIMEOUT_DEFAULT;
#ifdef CONFIG_OF
	alg_data->adapter.dev.of_node = of_node_get(pdev->dev.of_node);
	if (pdev->dev.of_node) {
		of_property_read_u32(pdev->dev.of_node, "clock-frequency",
				     &speed);
		/*
		 * At this point, it is planned to add an OF timeout property.
		 * As soon as there is a consensus about how to call and handle
		 * this, sth. like the following can be put here:
		 *
		 * of_property_read_u32(pdev->dev.of_node, "timeout",
		 *                      &alg_data->timeout);
		 */
	}
#endif
	alg_data->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(alg_data->clk))
		return PTR_ERR(alg_data->clk);

	timer_setup(&alg_data->mif.timer, i2c_pnx_timeout, 0);

	snprintf(alg_data->adapter.name, sizeof(alg_data->adapter.name),
		 "%s", pdev->name);

	/* Register I/O resource */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	alg_data->ioaddr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(alg_data->ioaddr))
		return PTR_ERR(alg_data->ioaddr);

	ret = clk_prepare_enable(alg_data->clk);
	if (ret)
		return ret;

	freq = clk_get_rate(alg_data->clk);

	/*
	 * Clock Divisor High This value is the number of system clocks
	 * the serial clock (SCL) will be high.
	 * For example, if the system clock period is 50 ns and the maximum
	 * desired serial period is 10000 ns (100 kHz), then CLKHI would be
	 * set to 0.5*(f_sys/f_i2c)-2=0.5*(20e6/100e3)-2=98. The actual value
	 * programmed into CLKHI will vary from this slightly due to
	 * variations in the output pad's rise and fall times as well as
	 * the deglitching filter length.
	 */

	tmp = (freq / speed) / 2 - 2;
	if (tmp > 0x3FF)
		tmp = 0x3FF;
	iowrite32(tmp, I2C_REG_CKH(alg_data));
	iowrite32(tmp, I2C_REG_CKL(alg_data));

	iowrite32(mcntrl_reset, I2C_REG_CTL(alg_data));
	if (wait_reset(alg_data)) {
		ret = -ENODEV;
		goto out_clock;
	}
	init_completion(&alg_data->mif.complete);

	alg_data->irq = platform_get_irq(pdev, 0);
	if (alg_data->irq < 0) {
		dev_err(&pdev->dev, "Failed to get IRQ from platform resource\n");
		ret = alg_data->irq;
		goto out_clock;
	}
	ret = devm_request_irq(&pdev->dev, alg_data->irq, i2c_pnx_interrupt,
			       0, pdev->name, alg_data);
	if (ret)
		goto out_clock;

	/* Register this adapter with the I2C subsystem */
	ret = i2c_add_numbered_adapter(&alg_data->adapter);
	if (ret < 0)
		goto out_clock;

	dev_dbg(&pdev->dev, "%s: Master at %#8x, irq %d.\n",
		alg_data->adapter.name, res->start, alg_data->irq);

	return 0;

out_clock:
	clk_disable_unprepare(alg_data->clk);
	return ret;
}