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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct ionic_lif {int /*<<< orphan*/  state; struct net_device* netdev; TYPE_1__* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  link_speed; int /*<<< orphan*/  link_status; } ;
struct TYPE_3__ {TYPE_2__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_LIF_LINK_CHECK_REQUESTED ; 
 int /*<<< orphan*/  IONIC_LIF_UP ; 
 scalar_t__ IONIC_PORT_OPER_STATUS_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ionic_link_status_check(struct ionic_lif *lif)
{
	struct net_device *netdev = lif->netdev;
	u16 link_status;
	bool link_up;

	link_status = le16_to_cpu(lif->info->status.link_status);
	link_up = link_status == IONIC_PORT_OPER_STATUS_UP;

	/* filter out the no-change cases */
	if (link_up == netif_carrier_ok(netdev))
		goto link_out;

	if (link_up) {
		netdev_info(netdev, "Link up - %d Gbps\n",
			    le32_to_cpu(lif->info->status.link_speed) / 1000);

		if (test_bit(IONIC_LIF_UP, lif->state)) {
			netif_tx_wake_all_queues(lif->netdev);
			netif_carrier_on(netdev);
		}
	} else {
		netdev_info(netdev, "Link down\n");

		/* carrier off first to avoid watchdog timeout */
		netif_carrier_off(netdev);
		if (test_bit(IONIC_LIF_UP, lif->state))
			netif_tx_stop_all_queues(netdev);
	}

link_out:
	clear_bit(IONIC_LIF_LINK_CHECK_REQUESTED, lif->state);
}