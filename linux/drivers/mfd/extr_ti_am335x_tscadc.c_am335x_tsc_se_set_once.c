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
struct ti_tscadc_dev {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SE ; 
 int /*<<< orphan*/  am335x_tscadc_need_adc (struct ti_tscadc_dev*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void am335x_tsc_se_set_once(struct ti_tscadc_dev *tscadc, u32 val)
{
	spin_lock_irq(&tscadc->reg_lock);
	am335x_tscadc_need_adc(tscadc);

	regmap_write(tscadc->regmap, REG_SE, val);
	spin_unlock_irq(&tscadc->reg_lock);
}