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
struct serio_raw {int dummy; } ;
struct serio_driver {int dummy; } ;
struct serio {int /*<<< orphan*/  dev; struct serio_driver* drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct serio_raw* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static int serio_raw_reconnect(struct serio *serio)
{
	struct serio_raw *serio_raw = serio_get_drvdata(serio);
	struct serio_driver *drv = serio->drv;

	if (!drv || !serio_raw) {
		dev_dbg(&serio->dev,
			"reconnect request, but serio is disconnected, ignoring...\n");
		return -1;
	}

	/*
	 * Nothing needs to be done here, we just need this method to
	 * keep the same device.
	 */
	return 0;
}