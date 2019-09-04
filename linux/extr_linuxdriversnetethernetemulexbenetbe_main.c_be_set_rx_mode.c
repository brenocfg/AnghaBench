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
struct net_device {int dummy; } ;
struct be_cmd_work {int /*<<< orphan*/  work; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 struct be_cmd_work* be_alloc_work (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_work_set_rx_mode ; 
 int /*<<< orphan*/  be_wq ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void be_set_rx_mode(struct net_device *dev)
{
	struct be_adapter *adapter = netdev_priv(dev);
	struct be_cmd_work *work;

	work = be_alloc_work(adapter, be_work_set_rx_mode);
	if (work)
		queue_work(be_wq, &work->work);
}