#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ dev; } ;
struct TYPE_4__ {TYPE_1__ connector; struct i2c_client* stdp4028_i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  STDP4028_DPTX_IRQ_CLEAR ; 
 int /*<<< orphan*/  STDP4028_DPTX_IRQ_STS_REG ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (scalar_t__) ; 
 TYPE_2__* ge_b850v3_lvds_ptr ; 
 int /*<<< orphan*/  i2c_smbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ge_b850v3_lvds_irq_handler(int irq, void *dev_id)
{
	struct i2c_client *stdp4028_i2c
			= ge_b850v3_lvds_ptr->stdp4028_i2c;

	i2c_smbus_write_word_data(stdp4028_i2c,
				  STDP4028_DPTX_IRQ_STS_REG,
				  STDP4028_DPTX_IRQ_CLEAR);

	if (ge_b850v3_lvds_ptr->connector.dev)
		drm_kms_helper_hotplug_event(ge_b850v3_lvds_ptr->connector.dev);

	return IRQ_HANDLED;
}