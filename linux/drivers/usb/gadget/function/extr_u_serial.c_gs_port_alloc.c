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
struct usb_cdc_line_coding {int dummy; } ;
struct gs_port {unsigned int port_num; struct usb_cdc_line_coding port_line_coding; int /*<<< orphan*/  write_pool; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  read_pool; int /*<<< orphan*/  push; int /*<<< orphan*/  close_wait; int /*<<< orphan*/  drain_wait; int /*<<< orphan*/  port_lock; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct gs_port* port; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_rx_push ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct gs_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* ports ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gs_port_alloc(unsigned port_num, struct usb_cdc_line_coding *coding)
{
	struct gs_port	*port;
	int		ret = 0;

	mutex_lock(&ports[port_num].lock);
	if (ports[port_num].port) {
		ret = -EBUSY;
		goto out;
	}

	port = kzalloc(sizeof(struct gs_port), GFP_KERNEL);
	if (port == NULL) {
		ret = -ENOMEM;
		goto out;
	}

	tty_port_init(&port->port);
	spin_lock_init(&port->port_lock);
	init_waitqueue_head(&port->drain_wait);
	init_waitqueue_head(&port->close_wait);

	INIT_DELAYED_WORK(&port->push, gs_rx_push);

	INIT_LIST_HEAD(&port->read_pool);
	INIT_LIST_HEAD(&port->read_queue);
	INIT_LIST_HEAD(&port->write_pool);

	port->port_num = port_num;
	port->port_line_coding = *coding;

	ports[port_num].port = port;
out:
	mutex_unlock(&ports[port_num].lock);
	return ret;
}