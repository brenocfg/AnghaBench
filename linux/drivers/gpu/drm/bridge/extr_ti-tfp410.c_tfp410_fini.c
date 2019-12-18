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
struct tfp410 {scalar_t__ hpd_irq; scalar_t__ hpd; scalar_t__ ddc; int /*<<< orphan*/  bridge; int /*<<< orphan*/  hpd_work; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct tfp410* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  i2c_put_adapter (scalar_t__) ; 

__attribute__((used)) static int tfp410_fini(struct device *dev)
{
	struct tfp410 *dvi = dev_get_drvdata(dev);

	if (dvi->hpd_irq >= 0)
		cancel_delayed_work_sync(&dvi->hpd_work);

	drm_bridge_remove(&dvi->bridge);

	if (dvi->ddc)
		i2c_put_adapter(dvi->ddc);
	if (dvi->hpd)
		gpiod_put(dvi->hpd);

	return 0;
}