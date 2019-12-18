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
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct xlp9xx_i2c_dev {int /*<<< orphan*/  ara; TYPE_1__ alert_data; int /*<<< orphan*/  adapter; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  i2c_setup_smbus_alert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int xlp9xx_i2c_smbus_setup(struct xlp9xx_i2c_dev *priv,
				  struct platform_device *pdev)
{
	if (!priv->alert_data.irq)
		return -EINVAL;

	priv->ara = i2c_setup_smbus_alert(&priv->adapter, &priv->alert_data);
	if (!priv->ara)
		return -ENODEV;

	return 0;
}