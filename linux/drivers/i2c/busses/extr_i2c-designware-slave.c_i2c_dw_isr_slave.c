#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dw_i2c_dev {int /*<<< orphan*/  cmd_complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int i2c_dw_irq_handler_slave (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_dw_read_clear_intrbits_slave (struct dw_i2c_dev*) ; 

__attribute__((used)) static irqreturn_t i2c_dw_isr_slave(int this_irq, void *dev_id)
{
	struct dw_i2c_dev *dev = dev_id;
	int ret;

	i2c_dw_read_clear_intrbits_slave(dev);
	ret = i2c_dw_irq_handler_slave(dev);
	if (ret > 0)
		complete(&dev->cmd_complete);

	return IRQ_RETVAL(ret);
}