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
typedef  scalar_t__ u8 ;
struct npcm7xx_pwm_fan_data {int* fan_irq; int /*<<< orphan*/ * fan_lock; int /*<<< orphan*/  fan_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  NPCM7XX_FAN_CMPA ; 
 int /*<<< orphan*/  NPCM7XX_FAN_CMPB ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TICTRL (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npcm7xx_check_cmp (struct npcm7xx_pwm_fan_data*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t npcm7xx_fan_isr(int irq, void *dev_id)
{
	struct npcm7xx_pwm_fan_data *data = dev_id;
	unsigned long flags;
	int module;
	u8 flag;

	module = irq - data->fan_irq[0];
	spin_lock_irqsave(&data->fan_lock[module], flags);

	flag = ioread8(NPCM7XX_FAN_REG_TICTRL(data->fan_base, module));
	if (flag > 0) {
		npcm7xx_check_cmp(data, module, NPCM7XX_FAN_CMPA, flag);
		npcm7xx_check_cmp(data, module, NPCM7XX_FAN_CMPB, flag);
		spin_unlock_irqrestore(&data->fan_lock[module], flags);
		return IRQ_HANDLED;
	}

	spin_unlock_irqrestore(&data->fan_lock[module], flags);

	return IRQ_NONE;
}