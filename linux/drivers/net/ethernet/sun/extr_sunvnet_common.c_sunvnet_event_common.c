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
struct vio_driver_state {TYPE_1__* vdev; } ;
struct vnet_port {int rx_event; int /*<<< orphan*/  napi; struct vio_driver_state vio; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_INTR_DISABLED ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vio_set_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sunvnet_event_common(void *arg, int event)
{
	struct vnet_port *port = arg;
	struct vio_driver_state *vio = &port->vio;

	port->rx_event |= event;
	vio_set_intr(vio->vdev->rx_ino, HV_INTR_DISABLED);
	napi_schedule(&port->napi);
}