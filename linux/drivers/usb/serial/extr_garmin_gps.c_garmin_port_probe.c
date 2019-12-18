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
struct usb_serial_port {int dummy; } ;
struct garmin_data {int /*<<< orphan*/  write_urbs; scalar_t__ count; scalar_t__ flags; scalar_t__ state; struct usb_serial_port* port; int /*<<< orphan*/  pktlist; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int garmin_init_session (struct usb_serial_port*) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct garmin_data*) ; 
 struct garmin_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_handler ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct garmin_data*) ; 

__attribute__((used)) static int garmin_port_probe(struct usb_serial_port *port)
{
	int status;
	struct garmin_data *garmin_data_p;

	garmin_data_p = kzalloc(sizeof(struct garmin_data), GFP_KERNEL);
	if (!garmin_data_p)
		return -ENOMEM;

	timer_setup(&garmin_data_p->timer, timeout_handler, 0);
	spin_lock_init(&garmin_data_p->lock);
	INIT_LIST_HEAD(&garmin_data_p->pktlist);
	garmin_data_p->port = port;
	garmin_data_p->state = 0;
	garmin_data_p->flags = 0;
	garmin_data_p->count = 0;
	init_usb_anchor(&garmin_data_p->write_urbs);
	usb_set_serial_port_data(port, garmin_data_p);

	status = garmin_init_session(port);
	if (status)
		goto err_free;

	return 0;
err_free:
	kfree(garmin_data_p);

	return status;
}