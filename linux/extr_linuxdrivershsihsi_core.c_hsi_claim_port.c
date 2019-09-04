#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct hsi_port {int shared; int /*<<< orphan*/  lock; scalar_t__ claimed; TYPE_1__ device; } ;
struct hsi_client {int pclaimed; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_hsi_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int hsi_claim_port(struct hsi_client *cl, unsigned int share)
{
	struct hsi_port *port = hsi_get_port(cl);
	int err = 0;

	mutex_lock(&port->lock);
	if ((port->claimed) && (!port->shared || !share)) {
		err = -EBUSY;
		goto out;
	}
	if (!try_module_get(to_hsi_controller(port->device.parent)->owner)) {
		err = -ENODEV;
		goto out;
	}
	port->claimed++;
	port->shared = !!share;
	cl->pclaimed = 1;
out:
	mutex_unlock(&port->lock);

	return err;
}