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
struct mc13783_ts_priv {int /*<<< orphan*/  work; int /*<<< orphan*/  mc13xxx; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC13XXX_ADC0 ; 
 int /*<<< orphan*/  MC13XXX_ADC0_TSMOD_MASK ; 
 int /*<<< orphan*/  MC13XXX_IRQ_TS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct mc13783_ts_priv* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mc13xxx_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mc13783_ts_priv*) ; 
 int /*<<< orphan*/  mc13xxx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc13xxx_reg_rmw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc13xxx_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mc13783_ts_close(struct input_dev *dev)
{
	struct mc13783_ts_priv *priv = input_get_drvdata(dev);

	mc13xxx_lock(priv->mc13xxx);
	mc13xxx_reg_rmw(priv->mc13xxx, MC13XXX_ADC0,
			MC13XXX_ADC0_TSMOD_MASK, 0);
	mc13xxx_irq_free(priv->mc13xxx, MC13XXX_IRQ_TS, priv);
	mc13xxx_unlock(priv->mc13xxx);

	cancel_delayed_work_sync(&priv->work);
}