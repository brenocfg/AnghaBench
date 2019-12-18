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
struct serio_driver {int dummy; } ;
struct serio {int /*<<< orphan*/  dev; struct serio_driver* drv; } ;
struct atkbd {scalar_t__ set; int /*<<< orphan*/  mutex; scalar_t__ write; scalar_t__ emul; scalar_t__ xl_bit; int /*<<< orphan*/  softrepeat; int /*<<< orphan*/  extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  atkbd_activate (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_disable (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_enable (struct atkbd*) ; 
 scalar_t__ atkbd_probe (struct atkbd*) ; 
 scalar_t__ atkbd_select_set (struct atkbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atkbd_set_leds (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_set_repeat_rate (struct atkbd*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct atkbd* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static int atkbd_reconnect(struct serio *serio)
{
	struct atkbd *atkbd = serio_get_drvdata(serio);
	struct serio_driver *drv = serio->drv;
	int retval = -1;

	if (!atkbd || !drv) {
		dev_dbg(&serio->dev,
			"reconnect request, but serio is disconnected, ignoring...\n");
		return -1;
	}

	mutex_lock(&atkbd->mutex);

	atkbd_disable(atkbd);

	if (atkbd->write) {
		if (atkbd_probe(atkbd))
			goto out;

		if (atkbd->set != atkbd_select_set(atkbd, atkbd->set, atkbd->extra))
			goto out;

		/*
		 * Restore LED state and repeat rate. While input core
		 * will do this for us at resume time reconnect may happen
		 * because user requested it via sysfs or simply because
		 * keyboard was unplugged and plugged in again so we need
		 * to do it ourselves here.
		 */
		atkbd_set_leds(atkbd);
		if (!atkbd->softrepeat)
			atkbd_set_repeat_rate(atkbd);

	}

	/*
	 * Reset our state machine in case reconnect happened in the middle
	 * of multi-byte scancode.
	 */
	atkbd->xl_bit = 0;
	atkbd->emul = 0;

	atkbd_enable(atkbd);
	if (atkbd->write)
		atkbd_activate(atkbd);

	retval = 0;

 out:
	mutex_unlock(&atkbd->mutex);
	return retval;
}