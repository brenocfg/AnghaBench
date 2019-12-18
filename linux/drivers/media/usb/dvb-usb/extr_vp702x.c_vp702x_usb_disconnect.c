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
struct vp702x_device_state {int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  buf; } ;
struct usb_interface {int dummy; } ;
struct dvb_usb_device {struct vp702x_device_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_usb_device_exit (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dvb_usb_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void vp702x_usb_disconnect(struct usb_interface *intf)
{
	struct dvb_usb_device *d = usb_get_intfdata(intf);
	struct vp702x_device_state *st = d->priv;
	mutex_lock(&st->buf_mutex);
	kfree(st->buf);
	mutex_unlock(&st->buf_mutex);
	dvb_usb_device_exit(intf);
}