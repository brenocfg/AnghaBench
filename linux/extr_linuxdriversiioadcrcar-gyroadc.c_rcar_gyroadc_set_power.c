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
struct rcar_gyroadc {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 

__attribute__((used)) static int rcar_gyroadc_set_power(struct rcar_gyroadc *priv, bool on)
{
	struct device *dev = priv->dev;
	int ret;

	if (on) {
		ret = pm_runtime_get_sync(dev);
		if (ret < 0)
			pm_runtime_put_noidle(dev);
	} else {
		pm_runtime_mark_last_busy(dev);
		ret = pm_runtime_put_autosuspend(dev);
	}

	return ret;
}