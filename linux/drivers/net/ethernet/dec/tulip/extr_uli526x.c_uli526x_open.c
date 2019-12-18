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
struct TYPE_5__ {scalar_t__ expires; } ;
struct uli526x_board_info {int cr6_data; int link_failed; int NIC_capability; int PHY_reg4; TYPE_2__ timer; TYPE_1__* pdev; int /*<<< orphan*/  cr0_data; scalar_t__ wait_reset; scalar_t__ rx_avail_cnt; scalar_t__ tx_packet_cnt; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR0_DEFAULT ; 
 int CR6_DEFAULT ; 
 int HZ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  ULI526X_DBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ULI526X_TIMER_WUT ; 
 int ULI526X_TXTH_256 ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 struct uli526x_board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uli526x_cr6_user_set ; 
 int /*<<< orphan*/  uli526x_init (struct net_device*) ; 
 int /*<<< orphan*/  uli526x_interrupt ; 
 int /*<<< orphan*/  uli526x_timer ; 

__attribute__((used)) static int uli526x_open(struct net_device *dev)
{
	int ret;
	struct uli526x_board_info *db = netdev_priv(dev);

	ULI526X_DBUG(0, "uli526x_open", 0);

	/* system variable init */
	db->cr6_data = CR6_DEFAULT | uli526x_cr6_user_set;
	db->tx_packet_cnt = 0;
	db->rx_avail_cnt = 0;
	db->link_failed = 1;
	netif_carrier_off(dev);
	db->wait_reset = 0;

	db->NIC_capability = 0xf;	/* All capability*/
	db->PHY_reg4 = 0x1e0;

	/* CR6 operation mode decision */
	db->cr6_data |= ULI526X_TXTH_256;
	db->cr0_data = CR0_DEFAULT;

	/* Initialize ULI526X board */
	uli526x_init(dev);

	ret = request_irq(db->pdev->irq, uli526x_interrupt, IRQF_SHARED,
			  dev->name, dev);
	if (ret)
		return ret;

	/* Active System Interface */
	netif_wake_queue(dev);

	/* set and active a timer process */
	timer_setup(&db->timer, uli526x_timer, 0);
	db->timer.expires = ULI526X_TIMER_WUT + HZ * 2;
	add_timer(&db->timer);

	return 0;
}