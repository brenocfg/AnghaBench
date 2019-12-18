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
typedef  int u8 ;
struct usb_function {int dummy; } ;
struct phonet_port {int /*<<< orphan*/  lock; int /*<<< orphan*/ * usb; } ;
struct f_phonet {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {unsigned int bInterfaceNumber; } ;
struct TYPE_3__ {unsigned int bInterfaceNumber; } ;

/* Variables and functions */
 int EINVAL ; 
 struct f_phonet* func_to_pn (struct usb_function*) ; 
 struct phonet_port* netdev_priv (int /*<<< orphan*/ ) ; 
 TYPE_2__ pn_control_intf_desc ; 
 TYPE_1__ pn_data_intf_desc ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pn_get_alt(struct usb_function *f, unsigned intf)
{
	struct f_phonet *fp = func_to_pn(f);

	if (intf == pn_control_intf_desc.bInterfaceNumber)
		return 0;

	if (intf == pn_data_intf_desc.bInterfaceNumber) {
		struct phonet_port *port = netdev_priv(fp->dev);
		u8 alt;

		spin_lock(&port->lock);
		alt = port->usb != NULL;
		spin_unlock(&port->lock);
		return alt;
	}

	return -EINVAL;
}