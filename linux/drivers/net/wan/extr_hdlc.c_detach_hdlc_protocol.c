#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * state; TYPE_1__* proto; } ;
typedef  TYPE_2__ hdlc_device ;
struct TYPE_4__ {int /*<<< orphan*/  module; int /*<<< orphan*/  (* detach ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_PRE_TYPE_CHANGE ; 
 int call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 TYPE_2__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_setup_dev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int notifier_to_errno (int) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

int detach_hdlc_protocol(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	int err;

	if (hdlc->proto) {
		err = call_netdevice_notifiers(NETDEV_PRE_TYPE_CHANGE, dev);
		err = notifier_to_errno(err);
		if (err) {
			netdev_err(dev, "Refused to change device type\n");
			return err;
		}

		if (hdlc->proto->detach)
			hdlc->proto->detach(dev);
		module_put(hdlc->proto->module);
		hdlc->proto = NULL;
	}
	kfree(hdlc->state);
	hdlc->state = NULL;
	hdlc_setup_dev(dev);

	return 0;
}