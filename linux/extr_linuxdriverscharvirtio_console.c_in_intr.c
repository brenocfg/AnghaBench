#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtqueue {TYPE_3__* vdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  hvc; } ;
struct port {TYPE_2__ cons; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  inbuf_lock; TYPE_1__* portdev; int /*<<< orphan*/  guest_connected; int /*<<< orphan*/  inbuf; } ;
struct TYPE_6__ {int /*<<< orphan*/  priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  discard_port_data (struct port*) ; 
 struct port* find_port_by_vq (int /*<<< orphan*/ ,struct virtqueue*) ; 
 int /*<<< orphan*/  flush_bufs (struct virtqueue*,int) ; 
 int /*<<< orphan*/  get_inbuf (struct port*) ; 
 int /*<<< orphan*/  hvc_kick () ; 
 scalar_t__ hvc_poll (int /*<<< orphan*/ ) ; 
 scalar_t__ is_console_port (struct port*) ; 
 int /*<<< orphan*/  is_rproc_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sigio_to_port (struct port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void in_intr(struct virtqueue *vq)
{
	struct port *port;
	unsigned long flags;

	port = find_port_by_vq(vq->vdev->priv, vq);
	if (!port) {
		flush_bufs(vq, false);
		return;
	}

	spin_lock_irqsave(&port->inbuf_lock, flags);
	port->inbuf = get_inbuf(port);

	/*
	 * Normally the port should not accept data when the port is
	 * closed. For generic serial ports, the host won't (shouldn't)
	 * send data till the guest is connected. But this condition
	 * can be reached when a console port is not yet connected (no
	 * tty is spawned) and the other side sends out data over the
	 * vring, or when a remote devices start sending data before
	 * the ports are opened.
	 *
	 * A generic serial port will discard data if not connected,
	 * while console ports and rproc-serial ports accepts data at
	 * any time. rproc-serial is initiated with guest_connected to
	 * false because port_fops_open expects this. Console ports are
	 * hooked up with an HVC console and is initialized with
	 * guest_connected to true.
	 */

	if (!port->guest_connected && !is_rproc_serial(port->portdev->vdev))
		discard_port_data(port);

	/* Send a SIGIO indicating new data in case the process asked for it */
	send_sigio_to_port(port);

	spin_unlock_irqrestore(&port->inbuf_lock, flags);

	wake_up_interruptible(&port->waitqueue);

	if (is_console_port(port) && hvc_poll(port->cons.hvc))
		hvc_kick();
}