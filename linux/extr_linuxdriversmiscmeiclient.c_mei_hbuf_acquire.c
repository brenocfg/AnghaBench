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
struct mei_device {int hbuf_is_ready; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MEI_PG_ON ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mei_pg_in_transition (struct mei_device*) ; 
 scalar_t__ mei_pg_state (struct mei_device*) ; 

bool mei_hbuf_acquire(struct mei_device *dev)
{
	if (mei_pg_state(dev) == MEI_PG_ON ||
	    mei_pg_in_transition(dev)) {
		dev_dbg(dev->dev, "device is in pg\n");
		return false;
	}

	if (!dev->hbuf_is_ready) {
		dev_dbg(dev->dev, "hbuf is not ready\n");
		return false;
	}

	dev->hbuf_is_ready = false;

	return true;
}