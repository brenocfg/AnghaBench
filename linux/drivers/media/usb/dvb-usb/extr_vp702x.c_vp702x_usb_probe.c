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
struct vp702x_device_state {int buf_len; int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  buf; } ;
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct dvb_usb_device {struct vp702x_device_state* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  dvb_usb_device_exit (struct usb_interface*) ; 
 int dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dvb_usb_device**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vp702x_properties ; 

__attribute__((used)) static int vp702x_usb_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct dvb_usb_device *d;
	struct vp702x_device_state *st;
	int ret;

	ret = dvb_usb_device_init(intf, &vp702x_properties,
				   THIS_MODULE, &d, adapter_nr);
	if (ret)
		goto out;

	st = d->priv;
	st->buf_len = 16;
	st->buf = kmalloc(st->buf_len, GFP_KERNEL);
	if (!st->buf) {
		ret = -ENOMEM;
		dvb_usb_device_exit(intf);
		goto out;
	}
	mutex_init(&st->buf_mutex);

out:
	return ret;

}