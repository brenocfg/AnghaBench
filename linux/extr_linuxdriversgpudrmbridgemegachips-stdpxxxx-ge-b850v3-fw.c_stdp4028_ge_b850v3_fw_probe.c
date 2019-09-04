#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct TYPE_5__ {TYPE_3__ bridge; struct i2c_client* stdp4028_i2c; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  STDP4028_DPTX_IRQ_CLEAR ; 
 int /*<<< orphan*/  STDP4028_DPTX_IRQ_STS_REG ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_3__*) ; 
 int /*<<< orphan*/  ge_b850v3_lvds_funcs ; 
 int /*<<< orphan*/  ge_b850v3_lvds_init (struct device*) ; 
 int /*<<< orphan*/  ge_b850v3_lvds_irq_handler ; 
 TYPE_1__* ge_b850v3_lvds_ptr ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_smbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stdp4028_ge_b850v3_fw_probe(struct i2c_client *stdp4028_i2c,
				       const struct i2c_device_id *id)
{
	struct device *dev = &stdp4028_i2c->dev;

	ge_b850v3_lvds_init(dev);

	ge_b850v3_lvds_ptr->stdp4028_i2c = stdp4028_i2c;
	i2c_set_clientdata(stdp4028_i2c, ge_b850v3_lvds_ptr);

	/* drm bridge initialization */
	ge_b850v3_lvds_ptr->bridge.funcs = &ge_b850v3_lvds_funcs;
	ge_b850v3_lvds_ptr->bridge.of_node = dev->of_node;
	drm_bridge_add(&ge_b850v3_lvds_ptr->bridge);

	/* Clear pending interrupts since power up. */
	i2c_smbus_write_word_data(stdp4028_i2c,
				  STDP4028_DPTX_IRQ_STS_REG,
				  STDP4028_DPTX_IRQ_CLEAR);

	if (!stdp4028_i2c->irq)
		return 0;

	return devm_request_threaded_irq(&stdp4028_i2c->dev,
			stdp4028_i2c->irq, NULL,
			ge_b850v3_lvds_irq_handler,
			IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
			"ge-b850v3-lvds-dp", ge_b850v3_lvds_ptr);
}