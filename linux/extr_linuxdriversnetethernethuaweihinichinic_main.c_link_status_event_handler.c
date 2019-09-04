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
typedef  int u16 ;
struct hinic_port_link_status {scalar_t__ link; scalar_t__ status; } ;
struct hinic_dev {int flags; int /*<<< orphan*/  netdev; int /*<<< orphan*/  mgmt_lock; } ;

/* Variables and functions */
 int HINIC_INTF_UP ; 
 scalar_t__ HINIC_LINK_STATE_UP ; 
 int HINIC_LINK_UP ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void link_status_event_handler(void *handle, void *buf_in, u16 in_size,
				      void *buf_out, u16 *out_size)
{
	struct hinic_port_link_status *link_status, *ret_link_status;
	struct hinic_dev *nic_dev = handle;

	link_status = buf_in;

	if (link_status->link == HINIC_LINK_STATE_UP) {
		down(&nic_dev->mgmt_lock);

		nic_dev->flags |= HINIC_LINK_UP;

		if ((nic_dev->flags & (HINIC_LINK_UP | HINIC_INTF_UP)) ==
		    (HINIC_LINK_UP | HINIC_INTF_UP)) {
			netif_carrier_on(nic_dev->netdev);
			netif_tx_wake_all_queues(nic_dev->netdev);
		}

		up(&nic_dev->mgmt_lock);

		netif_info(nic_dev, drv, nic_dev->netdev, "HINIC_Link is UP\n");
	} else {
		down(&nic_dev->mgmt_lock);

		nic_dev->flags &= ~HINIC_LINK_UP;

		netif_carrier_off(nic_dev->netdev);
		netif_tx_disable(nic_dev->netdev);

		up(&nic_dev->mgmt_lock);

		netif_info(nic_dev, drv, nic_dev->netdev, "HINIC_Link is DOWN\n");
	}

	ret_link_status = buf_out;
	ret_link_status->status = 0;

	*out_size = sizeof(*ret_link_status);
}