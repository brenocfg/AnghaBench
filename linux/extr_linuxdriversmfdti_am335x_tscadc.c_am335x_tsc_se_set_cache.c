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
typedef  int /*<<< orphan*/  u32 ;
struct ti_tscadc_dev {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  reg_se_cache; int /*<<< orphan*/  regmap; int /*<<< orphan*/  adc_in_use; int /*<<< orphan*/  reg_se_wait; scalar_t__ adc_waiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SE ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void am335x_tsc_se_set_cache(struct ti_tscadc_dev *tscadc, u32 val)
{
	unsigned long flags;

	spin_lock_irqsave(&tscadc->reg_lock, flags);
	tscadc->reg_se_cache |= val;
	if (tscadc->adc_waiting)
		wake_up(&tscadc->reg_se_wait);
	else if (!tscadc->adc_in_use)
		regmap_write(tscadc->regmap, REG_SE, tscadc->reg_se_cache);

	spin_unlock_irqrestore(&tscadc->reg_lock, flags);
}