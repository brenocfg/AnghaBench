#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct usnic_ib_dev {int /*<<< orphan*/  usdev_lock; TYPE_2__ ib_dev; TYPE_3__* ufdev; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_address; } ;
struct TYPE_5__ {int port_num; } ;
struct ib_event {TYPE_1__ element; TYPE_2__* device; void* event; } ;
struct TYPE_7__ {int /*<<< orphan*/  inaddr; } ;

/* Variables and functions */
 void* IB_EVENT_GID_CHANGE ; 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/ * dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_cmd_to_name (unsigned long) ; 
 int /*<<< orphan*/  usnic_fwd_add_ipaddr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_fwd_del_ipaddr (TYPE_3__*) ; 
 int /*<<< orphan*/  usnic_ib_qp_grp_modify_active_to_err (struct usnic_ib_dev*) ; 
 int /*<<< orphan*/  usnic_info (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int usnic_ib_handle_inet_event(struct usnic_ib_dev *us_ibdev,
					unsigned long event, void *ptr)
{
	struct in_ifaddr *ifa = ptr;
	struct ib_event ib_event;

	mutex_lock(&us_ibdev->usdev_lock);

	switch (event) {
	case NETDEV_DOWN:
		usnic_info("%s via ip notifiers",
				netdev_cmd_to_name(event));
		usnic_fwd_del_ipaddr(us_ibdev->ufdev);
		usnic_ib_qp_grp_modify_active_to_err(us_ibdev);
		ib_event.event = IB_EVENT_GID_CHANGE;
		ib_event.device = &us_ibdev->ib_dev;
		ib_event.element.port_num = 1;
		ib_dispatch_event(&ib_event);
		break;
	case NETDEV_UP:
		usnic_fwd_add_ipaddr(us_ibdev->ufdev, ifa->ifa_address);
		usnic_info("%s via ip notifiers: ip %pI4",
				netdev_cmd_to_name(event),
				&us_ibdev->ufdev->inaddr);
		ib_event.event = IB_EVENT_GID_CHANGE;
		ib_event.device = &us_ibdev->ib_dev;
		ib_event.element.port_num = 1;
		ib_dispatch_event(&ib_event);
		break;
	default:
		usnic_info("Ignoring event %s on %s",
				netdev_cmd_to_name(event),
				dev_name(&us_ibdev->ib_dev.dev));
	}
	mutex_unlock(&us_ibdev->usdev_lock);

	return NOTIFY_DONE;
}