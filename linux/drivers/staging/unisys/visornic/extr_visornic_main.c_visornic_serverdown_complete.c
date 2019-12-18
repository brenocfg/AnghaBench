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
struct TYPE_2__ {scalar_t__ got_xmit_done; scalar_t__ sent_xmit; } ;
struct visornic_devdata {int server_down; int server_change_state; int /*<<< orphan*/  (* server_down_complete_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; TYPE_1__ chstat; int /*<<< orphan*/  num_rcvbuf_in_iovm; int /*<<< orphan*/  irq_poll_timer; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void visornic_serverdown_complete(struct visornic_devdata *devdata)
{
	struct net_device *netdev = devdata->netdev;

	/* Stop polling for interrupts */
	del_timer_sync(&devdata->irq_poll_timer);

	rtnl_lock();
	dev_close(netdev);
	rtnl_unlock();

	atomic_set(&devdata->num_rcvbuf_in_iovm, 0);
	devdata->chstat.sent_xmit = 0;
	devdata->chstat.got_xmit_done = 0;

	if (devdata->server_down_complete_func)
		(*devdata->server_down_complete_func)(devdata->dev, 0);

	devdata->server_down = true;
	devdata->server_change_state = false;
	devdata->server_down_complete_func = NULL;
}