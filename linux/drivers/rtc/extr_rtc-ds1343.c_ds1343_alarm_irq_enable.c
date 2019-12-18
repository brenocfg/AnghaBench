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
struct ds1343_priv {scalar_t__ irq; int /*<<< orphan*/  mutex; int /*<<< orphan*/  irqen; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTC_AF ; 
 struct ds1343_priv* dev_get_drvdata (struct device*) ; 
 int ds1343_update_alarm (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1343_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct ds1343_priv *priv = dev_get_drvdata(dev);
	int res = 0;

	if (priv->irq <= 0)
		return -EINVAL;

	mutex_lock(&priv->mutex);

	if (enabled)
		priv->irqen |= RTC_AF;
	else
		priv->irqen &= ~RTC_AF;

	res = ds1343_update_alarm(dev);

	mutex_unlock(&priv->mutex);

	return res;
}