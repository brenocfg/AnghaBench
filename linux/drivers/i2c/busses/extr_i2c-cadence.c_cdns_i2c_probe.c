#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct TYPE_19__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {struct cdns_platform_data* data; } ;
struct cdns_platform_data {int /*<<< orphan*/  quirks; } ;
struct TYPE_18__ {TYPE_2__* parent; int /*<<< orphan*/  of_node; } ;
struct TYPE_20__ {int retries; int /*<<< orphan*/  name; TYPE_1__ dev; struct cdns_i2c* algo_data; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct TYPE_17__ {int /*<<< orphan*/  notifier_call; } ;
struct cdns_i2c {int irq; int i2c_clk; int /*<<< orphan*/  clk; TYPE_8__ adap; int /*<<< orphan*/  input_clk; TYPE_16__ clk_rate_change_nb; TYPE_2__* dev; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  membase; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int CDNS_I2C_CR_ACK_EN ; 
 int CDNS_I2C_CR_MS ; 
 int CDNS_I2C_CR_NEA ; 
 int /*<<< orphan*/  CDNS_I2C_CR_OFFSET ; 
 int CDNS_I2C_SPEED_DEFAULT ; 
 int CDNS_I2C_SPEED_MAX ; 
 int /*<<< orphan*/  CDNS_I2C_TIMEOUT ; 
 int CDNS_I2C_TIMEOUT_MAX ; 
 int /*<<< orphan*/  CDNS_I2C_TIME_OUT_OFFSET ; 
 int /*<<< orphan*/  CNDS_I2C_PM_TIMEOUT ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cdns_i2c_algo ; 
 int /*<<< orphan*/  cdns_i2c_clk_notifier_cb ; 
 int /*<<< orphan*/  cdns_i2c_isr ; 
 int /*<<< orphan*/  cdns_i2c_of_match ; 
 int cdns_i2c_setclk (int /*<<< orphan*/ ,struct cdns_i2c*) ; 
 int /*<<< orphan*/  cdns_i2c_writereg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_notifier_register (int /*<<< orphan*/ ,TYPE_16__*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int,unsigned long,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct cdns_i2c* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cdns_i2c*) ; 
 int i2c_add_adapter (TYPE_8__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cdns_i2c*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned long) ; 

__attribute__((used)) static int cdns_i2c_probe(struct platform_device *pdev)
{
	struct resource *r_mem;
	struct cdns_i2c *id;
	int ret;
	const struct of_device_id *match;

	id = devm_kzalloc(&pdev->dev, sizeof(*id), GFP_KERNEL);
	if (!id)
		return -ENOMEM;

	id->dev = &pdev->dev;
	platform_set_drvdata(pdev, id);

	match = of_match_node(cdns_i2c_of_match, pdev->dev.of_node);
	if (match && match->data) {
		const struct cdns_platform_data *data = match->data;
		id->quirks = data->quirks;
	}

	r_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	id->membase = devm_ioremap_resource(&pdev->dev, r_mem);
	if (IS_ERR(id->membase))
		return PTR_ERR(id->membase);

	id->irq = platform_get_irq(pdev, 0);

	id->adap.owner = THIS_MODULE;
	id->adap.dev.of_node = pdev->dev.of_node;
	id->adap.algo = &cdns_i2c_algo;
	id->adap.timeout = CDNS_I2C_TIMEOUT;
	id->adap.retries = 3;		/* Default retry value. */
	id->adap.algo_data = id;
	id->adap.dev.parent = &pdev->dev;
	init_completion(&id->xfer_done);
	snprintf(id->adap.name, sizeof(id->adap.name),
		 "Cadence I2C at %08lx", (unsigned long)r_mem->start);

	id->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(id->clk)) {
		dev_err(&pdev->dev, "input clock not found.\n");
		return PTR_ERR(id->clk);
	}
	ret = clk_prepare_enable(id->clk);
	if (ret)
		dev_err(&pdev->dev, "Unable to enable clock.\n");

	pm_runtime_enable(id->dev);
	pm_runtime_set_autosuspend_delay(id->dev, CNDS_I2C_PM_TIMEOUT);
	pm_runtime_use_autosuspend(id->dev);
	pm_runtime_set_active(id->dev);

	id->clk_rate_change_nb.notifier_call = cdns_i2c_clk_notifier_cb;
	if (clk_notifier_register(id->clk, &id->clk_rate_change_nb))
		dev_warn(&pdev->dev, "Unable to register clock notifier.\n");
	id->input_clk = clk_get_rate(id->clk);

	ret = of_property_read_u32(pdev->dev.of_node, "clock-frequency",
			&id->i2c_clk);
	if (ret || (id->i2c_clk > CDNS_I2C_SPEED_MAX))
		id->i2c_clk = CDNS_I2C_SPEED_DEFAULT;

	cdns_i2c_writereg(CDNS_I2C_CR_ACK_EN | CDNS_I2C_CR_NEA | CDNS_I2C_CR_MS,
			  CDNS_I2C_CR_OFFSET);

	ret = cdns_i2c_setclk(id->input_clk, id);
	if (ret) {
		dev_err(&pdev->dev, "invalid SCL clock: %u Hz\n", id->i2c_clk);
		ret = -EINVAL;
		goto err_clk_dis;
	}

	ret = devm_request_irq(&pdev->dev, id->irq, cdns_i2c_isr, 0,
				 DRIVER_NAME, id);
	if (ret) {
		dev_err(&pdev->dev, "cannot get irq %d\n", id->irq);
		goto err_clk_dis;
	}

	/*
	 * Cadence I2C controller has a bug wherein it generates
	 * invalid read transaction after HW timeout in master receiver mode.
	 * HW timeout is not used by this driver and the interrupt is disabled.
	 * But the feature itself cannot be disabled. Hence maximum value
	 * is written to this register to reduce the chances of error.
	 */
	cdns_i2c_writereg(CDNS_I2C_TIMEOUT_MAX, CDNS_I2C_TIME_OUT_OFFSET);

	ret = i2c_add_adapter(&id->adap);
	if (ret < 0)
		goto err_clk_dis;

	dev_info(&pdev->dev, "%u kHz mmio %08lx irq %d\n",
		 id->i2c_clk / 1000, (unsigned long)r_mem->start, id->irq);

	return 0;

err_clk_dis:
	clk_disable_unprepare(id->clk);
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	return ret;
}