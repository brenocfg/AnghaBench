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
struct vio_driver_state {TYPE_1__* vdev; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct vcc_port {int /*<<< orphan*/  lock; scalar_t__ removed; int /*<<< orphan*/  tty; struct vio_driver_state vio; TYPE_2__ rx_timer; } ;
struct timer_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_irq; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct vcc_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct vcc_port* port ; 
 int /*<<< orphan*/  rx_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vcc_ldc_read (struct vcc_port*) ; 
 int /*<<< orphan*/  vcc_put (struct vcc_port*,int) ; 
 int /*<<< orphan*/  vio_conn_reset (struct vio_driver_state*) ; 

__attribute__((used)) static void vcc_rx_timer(struct timer_list *t)
{
	struct vcc_port *port = from_timer(port, t, rx_timer);
	struct vio_driver_state *vio;
	unsigned long flags;
	int rv;

	spin_lock_irqsave(&port->lock, flags);
	port->rx_timer.expires = 0;

	vio = &port->vio;

	enable_irq(vio->vdev->rx_irq);

	if (!port->tty || port->removed)
		goto done;

	rv = vcc_ldc_read(port);
	if (rv == -ECONNRESET)
		vio_conn_reset(vio);

done:
	spin_unlock_irqrestore(&port->lock, flags);
	vcc_put(port, false);
}