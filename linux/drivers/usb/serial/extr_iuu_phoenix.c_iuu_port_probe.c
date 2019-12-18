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
struct iuu_private {struct iuu_private* buf; struct iuu_private* writebuf; int /*<<< orphan*/  lock; int /*<<< orphan*/  vcc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int iuu_create_sysfs_attrs (struct usb_serial_port*) ; 
 int /*<<< orphan*/  kfree (struct iuu_private*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct iuu_private*) ; 
 int /*<<< orphan*/  vcc_default ; 

__attribute__((used)) static int iuu_port_probe(struct usb_serial_port *port)
{
	struct iuu_private *priv;
	int ret;

	priv = kzalloc(sizeof(struct iuu_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->buf = kzalloc(256, GFP_KERNEL);
	if (!priv->buf) {
		kfree(priv);
		return -ENOMEM;
	}

	priv->writebuf = kzalloc(256, GFP_KERNEL);
	if (!priv->writebuf) {
		kfree(priv->buf);
		kfree(priv);
		return -ENOMEM;
	}

	priv->vcc = vcc_default;
	spin_lock_init(&priv->lock);

	usb_set_serial_port_data(port, priv);

	ret = iuu_create_sysfs_attrs(port);
	if (ret) {
		kfree(priv->writebuf);
		kfree(priv->buf);
		kfree(priv);
		return ret;
	}

	return 0;
}