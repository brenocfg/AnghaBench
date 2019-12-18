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
struct hsi_port {scalar_t__ claimed; int /*<<< orphan*/  lock; TYPE_1__ device; scalar_t__ shared; int /*<<< orphan*/  (* release ) (struct hsi_client*) ;} ;
struct hsi_client {scalar_t__ pclaimed; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hsi_client*) ; 
 TYPE_2__* to_hsi_controller (int /*<<< orphan*/ ) ; 

void hsi_release_port(struct hsi_client *cl)
{
	struct hsi_port *port = hsi_get_port(cl);

	mutex_lock(&port->lock);
	/* Allow HW driver to do some cleanup */
	port->release(cl);
	if (cl->pclaimed)
		port->claimed--;
	BUG_ON(port->claimed < 0);
	cl->pclaimed = 0;
	if (!port->claimed)
		port->shared = 0;
	module_put(to_hsi_controller(port->device.parent)->owner);
	mutex_unlock(&port->lock);
}