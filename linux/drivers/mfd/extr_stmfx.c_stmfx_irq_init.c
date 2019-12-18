#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stmfx {TYPE_1__* dev; int /*<<< orphan*/  map; int /*<<< orphan*/  irq_domain; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int IRQF_ONESHOT ; 
 int IRQ_TYPE_EDGE_RISING ; 
 int IRQ_TYPE_LEVEL_HIGH ; 
 int /*<<< orphan*/  STMFX_REG_IRQ_OUT_PIN ; 
 int STMFX_REG_IRQ_OUT_PIN_POL ; 
 int STMFX_REG_IRQ_OUT_PIN_TYPE ; 
 int /*<<< orphan*/  STMFX_REG_IRQ_SRC_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct stmfx*) ; 
 struct stmfx* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  irq_domain_add_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct stmfx*) ; 
 int irq_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stmfx_irq_exit (struct i2c_client*) ; 
 int /*<<< orphan*/  stmfx_irq_handler ; 
 int /*<<< orphan*/  stmfx_irq_ops ; 

__attribute__((used)) static int stmfx_irq_init(struct i2c_client *client)
{
	struct stmfx *stmfx = i2c_get_clientdata(client);
	u32 irqoutpin = 0, irqtrigger;
	int ret;

	stmfx->irq_domain = irq_domain_add_simple(stmfx->dev->of_node,
						  STMFX_REG_IRQ_SRC_MAX, 0,
						  &stmfx_irq_ops, stmfx);
	if (!stmfx->irq_domain) {
		dev_err(stmfx->dev, "Failed to create IRQ domain\n");
		return -EINVAL;
	}

	if (!of_property_read_bool(stmfx->dev->of_node, "drive-open-drain"))
		irqoutpin |= STMFX_REG_IRQ_OUT_PIN_TYPE;

	irqtrigger = irq_get_trigger_type(client->irq);
	if ((irqtrigger & IRQ_TYPE_EDGE_RISING) ||
	    (irqtrigger & IRQ_TYPE_LEVEL_HIGH))
		irqoutpin |= STMFX_REG_IRQ_OUT_PIN_POL;

	ret = regmap_write(stmfx->map, STMFX_REG_IRQ_OUT_PIN, irqoutpin);
	if (ret)
		return ret;

	ret = devm_request_threaded_irq(stmfx->dev, client->irq,
					NULL, stmfx_irq_handler,
					irqtrigger | IRQF_ONESHOT,
					"stmfx", stmfx);
	if (ret)
		stmfx_irq_exit(client);

	return ret;
}