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
struct cdns3_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; TYPE_1__* gadget_driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdns3_disconnect_gadget(struct cdns3_device *priv_dev)
{
	if (priv_dev->gadget_driver && priv_dev->gadget_driver->disconnect) {
		spin_unlock(&priv_dev->lock);
		priv_dev->gadget_driver->disconnect(&priv_dev->gadget);
		spin_lock(&priv_dev->lock);
	}
}