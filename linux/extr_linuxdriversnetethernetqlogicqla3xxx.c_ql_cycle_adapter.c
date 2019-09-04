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
struct ql3_adapter {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ql_adapter_down (struct ql3_adapter*,int) ; 
 scalar_t__ ql_adapter_up (struct ql3_adapter*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int ql_cycle_adapter(struct ql3_adapter *qdev, int reset)
{
	if (ql_adapter_down(qdev, reset) || ql_adapter_up(qdev)) {
		netdev_err(qdev->ndev,
			   "Driver up/down cycle failed, closing device\n");
		rtnl_lock();
		dev_close(qdev->ndev);
		rtnl_unlock();
		return -1;
	}
	return 0;
}