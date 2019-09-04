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
typedef  scalar_t__ u16 ;
struct wl1273_device {scalar_t__ tx_power; struct wl1273_core* core; } ;
struct wl1273_core {scalar_t__ mode; int (* write ) (struct wl1273_core*,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ WL1273_MODE_OFF ; 
 scalar_t__ WL1273_MODE_SUSPENDED ; 
 int /*<<< orphan*/  WL1273_POWER_LEV_SET ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct wl1273_core*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wl1273_fm_set_tx_power(struct wl1273_device *radio, u16 power)
{
	struct wl1273_core *core = radio->core;
	int r;

	if (core->mode == WL1273_MODE_OFF ||
	    core->mode == WL1273_MODE_SUSPENDED)
		return -EPERM;

	mutex_lock(&core->lock);

	/* Convert the dBuV value to chip presentation */
	r = core->write(core, WL1273_POWER_LEV_SET, 122 - power);
	if (r)
		goto out;

	radio->tx_power = power;

out:
	mutex_unlock(&core->lock);
	return r;
}