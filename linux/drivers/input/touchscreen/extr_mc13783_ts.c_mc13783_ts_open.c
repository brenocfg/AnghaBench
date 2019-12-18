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
struct mc13783_ts_priv {int /*<<< orphan*/  mc13xxx; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC13783_TS_NAME ; 
 int /*<<< orphan*/  MC13XXX_ADC0 ; 
 int /*<<< orphan*/  MC13XXX_ADC0_TSMOD0 ; 
 int /*<<< orphan*/  MC13XXX_ADC0_TSMOD_MASK ; 
 int /*<<< orphan*/  MC13XXX_IRQ_TS ; 
 struct mc13783_ts_priv* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mc13783_ts_handler ; 
 int /*<<< orphan*/  mc13xxx_irq_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc13xxx_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mc13783_ts_priv*) ; 
 int mc13xxx_irq_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mc13783_ts_priv*) ; 
 int /*<<< orphan*/  mc13xxx_lock (int /*<<< orphan*/ ) ; 
 int mc13xxx_reg_rmw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc13xxx_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mc13783_ts_open(struct input_dev *dev)
{
	struct mc13783_ts_priv *priv = input_get_drvdata(dev);
	int ret;

	mc13xxx_lock(priv->mc13xxx);

	mc13xxx_irq_ack(priv->mc13xxx, MC13XXX_IRQ_TS);

	ret = mc13xxx_irq_request(priv->mc13xxx, MC13XXX_IRQ_TS,
		mc13783_ts_handler, MC13783_TS_NAME, priv);
	if (ret)
		goto out;

	ret = mc13xxx_reg_rmw(priv->mc13xxx, MC13XXX_ADC0,
			MC13XXX_ADC0_TSMOD_MASK, MC13XXX_ADC0_TSMOD0);
	if (ret)
		mc13xxx_irq_free(priv->mc13xxx, MC13XXX_IRQ_TS, priv);
out:
	mc13xxx_unlock(priv->mc13xxx);
	return ret;
}