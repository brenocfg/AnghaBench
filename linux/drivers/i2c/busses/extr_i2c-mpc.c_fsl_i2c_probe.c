#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {scalar_t__ start; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {struct mpc_i2c_data* data; } ;
struct mpc_i2c_data {int /*<<< orphan*/  (* setup ) (int /*<<< orphan*/ ,struct mpc_i2c*,int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct TYPE_11__ {int timeout; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct mpc_i2c {int /*<<< orphan*/  base; scalar_t__ irq; struct clk* clk_per; TYPE_3__ adap; TYPE_2__* dev; int /*<<< orphan*/  queue; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int const HZ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int MPC_I2C_CLOCK_LEGACY ; 
 int MPC_I2C_CLOCK_PRESERVE ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int) ; 
 struct clk* devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct mpc_i2c*) ; 
 int i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_3__*,struct mpc_i2c*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 scalar_t__ irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mpc_i2c*) ; 
 struct mpc_i2c* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_i2c_isr ; 
 int /*<<< orphan*/  mpc_i2c_of_match ; 
 int /*<<< orphan*/  mpc_i2c_setup_8xxx (int /*<<< orphan*/ ,struct mpc_i2c*,int) ; 
 TYPE_3__ mpc_ops ; 
 int /*<<< orphan*/  of_address_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 int* of_get_property (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_node_get (int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mpc_i2c*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mpc_i2c*) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,unsigned long long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct mpc_i2c*,int) ; 

__attribute__((used)) static int fsl_i2c_probe(struct platform_device *op)
{
	const struct of_device_id *match;
	struct mpc_i2c *i2c;
	const u32 *prop;
	u32 clock = MPC_I2C_CLOCK_LEGACY;
	int result = 0;
	int plen;
	struct resource res;
	struct clk *clk;
	int err;

	match = of_match_device(mpc_i2c_of_match, &op->dev);
	if (!match)
		return -EINVAL;

	i2c = kzalloc(sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	i2c->dev = &op->dev; /* for debug and error output */

	init_waitqueue_head(&i2c->queue);

	i2c->base = of_iomap(op->dev.of_node, 0);
	if (!i2c->base) {
		dev_err(i2c->dev, "failed to map controller\n");
		result = -ENOMEM;
		goto fail_map;
	}

	i2c->irq = irq_of_parse_and_map(op->dev.of_node, 0);
	if (i2c->irq) { /* no i2c->irq implies polling */
		result = request_irq(i2c->irq, mpc_i2c_isr,
				     IRQF_SHARED, "i2c-mpc", i2c);
		if (result < 0) {
			dev_err(i2c->dev, "failed to attach interrupt\n");
			goto fail_request;
		}
	}

	/*
	 * enable clock for the I2C peripheral (non fatal),
	 * keep a reference upon successful allocation
	 */
	clk = devm_clk_get(&op->dev, NULL);
	if (!IS_ERR(clk)) {
		err = clk_prepare_enable(clk);
		if (err) {
			dev_err(&op->dev, "failed to enable clock\n");
			goto fail_request;
		} else {
			i2c->clk_per = clk;
		}
	}

	if (of_property_read_bool(op->dev.of_node, "fsl,preserve-clocking")) {
		clock = MPC_I2C_CLOCK_PRESERVE;
	} else {
		prop = of_get_property(op->dev.of_node, "clock-frequency",
					&plen);
		if (prop && plen == sizeof(u32))
			clock = *prop;
	}

	if (match->data) {
		const struct mpc_i2c_data *data = match->data;
		data->setup(op->dev.of_node, i2c, clock);
	} else {
		/* Backwards compatibility */
		if (of_get_property(op->dev.of_node, "dfsrr", NULL))
			mpc_i2c_setup_8xxx(op->dev.of_node, i2c, clock);
	}

	prop = of_get_property(op->dev.of_node, "fsl,timeout", &plen);
	if (prop && plen == sizeof(u32)) {
		mpc_ops.timeout = *prop * HZ / 1000000;
		if (mpc_ops.timeout < 5)
			mpc_ops.timeout = 5;
	}
	dev_info(i2c->dev, "timeout %u us\n", mpc_ops.timeout * 1000000 / HZ);

	platform_set_drvdata(op, i2c);

	i2c->adap = mpc_ops;
	of_address_to_resource(op->dev.of_node, 0, &res);
	scnprintf(i2c->adap.name, sizeof(i2c->adap.name),
		  "MPC adapter at 0x%llx", (unsigned long long)res.start);
	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.dev.parent = &op->dev;
	i2c->adap.dev.of_node = of_node_get(op->dev.of_node);

	result = i2c_add_adapter(&i2c->adap);
	if (result < 0)
		goto fail_add;

	return result;

 fail_add:
	if (i2c->clk_per)
		clk_disable_unprepare(i2c->clk_per);
	free_irq(i2c->irq, i2c);
 fail_request:
	irq_dispose_mapping(i2c->irq);
	iounmap(i2c->base);
 fail_map:
	kfree(i2c);
	return result;
}