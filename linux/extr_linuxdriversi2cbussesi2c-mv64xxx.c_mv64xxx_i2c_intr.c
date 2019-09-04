#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ control; scalar_t__ status; } ;
struct mv64xxx_i2c_data {int cntl_bits; int /*<<< orphan*/  lock; TYPE_1__ reg_offsets; scalar_t__ reg_base; scalar_t__ irq_clear_inverted; scalar_t__ offload_enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MV64XXX_I2C_REG_CONTROL_IFLG ; 
 int /*<<< orphan*/  mv64xxx_i2c_do_action (struct mv64xxx_i2c_data*) ; 
 int /*<<< orphan*/  mv64xxx_i2c_fsm (struct mv64xxx_i2c_data*,int) ; 
 int /*<<< orphan*/  mv64xxx_i2c_intr_offload (struct mv64xxx_i2c_data*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t
mv64xxx_i2c_intr(int irq, void *dev_id)
{
	struct mv64xxx_i2c_data	*drv_data = dev_id;
	unsigned long	flags;
	u32		status;
	irqreturn_t	rc = IRQ_NONE;

	spin_lock_irqsave(&drv_data->lock, flags);

	if (drv_data->offload_enabled)
		rc = mv64xxx_i2c_intr_offload(drv_data);

	while (readl(drv_data->reg_base + drv_data->reg_offsets.control) &
						MV64XXX_I2C_REG_CONTROL_IFLG) {
		status = readl(drv_data->reg_base + drv_data->reg_offsets.status);
		mv64xxx_i2c_fsm(drv_data, status);
		mv64xxx_i2c_do_action(drv_data);

		if (drv_data->irq_clear_inverted)
			writel(drv_data->cntl_bits | MV64XXX_I2C_REG_CONTROL_IFLG,
			       drv_data->reg_base + drv_data->reg_offsets.control);

		rc = IRQ_HANDLED;
	}
	spin_unlock_irqrestore(&drv_data->lock, flags);

	return rc;
}