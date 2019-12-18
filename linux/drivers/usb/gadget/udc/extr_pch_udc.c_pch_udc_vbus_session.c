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
struct pch_udc_dev {int vbus_session; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pch_udc_reconnect (struct pch_udc_dev*) ; 
 int /*<<< orphan*/  pch_udc_set_disconnect (struct pch_udc_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pch_udc_vbus_session(struct pch_udc_dev *dev,
					  int is_active)
{
	if (is_active) {
		pch_udc_reconnect(dev);
		dev->vbus_session = 1;
	} else {
		if (dev->driver && dev->driver->disconnect) {
			spin_lock(&dev->lock);
			dev->driver->disconnect(&dev->gadget);
			spin_unlock(&dev->lock);
		}
		pch_udc_set_disconnect(dev);
		dev->vbus_session = 0;
	}
}