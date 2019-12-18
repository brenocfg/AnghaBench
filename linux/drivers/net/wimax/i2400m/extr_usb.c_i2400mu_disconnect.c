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
struct device {int dummy; } ;
struct usb_interface {struct device dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* net_dev; } ;
struct i2400m {TYPE_1__ wimax_dev; } ;
struct i2400mu {int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  debugfs_dentry; struct i2400m i2400m; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct usb_interface*,struct i2400m*) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct usb_interface*,struct i2400m*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  i2400m_release (struct i2400m*) ; 
 struct i2400mu* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void i2400mu_disconnect(struct usb_interface *iface)
{
	struct i2400mu *i2400mu = usb_get_intfdata(iface);
	struct i2400m *i2400m = &i2400mu->i2400m;
	struct net_device *net_dev = i2400m->wimax_dev.net_dev;
	struct device *dev = &iface->dev;

	d_fnstart(3, dev, "(iface %p i2400m %p)\n", iface, i2400m);

	debugfs_remove_recursive(i2400mu->debugfs_dentry);
	i2400m_release(i2400m);
	usb_set_intfdata(iface, NULL);
	usb_put_dev(i2400mu->usb_dev);
	free_netdev(net_dev);
	d_fnend(3, dev, "(iface %p i2400m %p) = void\n", iface, i2400m);
}