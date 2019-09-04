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
struct ql3_adapter {int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ADAPTER_UP ; 
 int /*<<< orphan*/  QL_DO_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ql3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ql_adapter_down (struct ql3_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql3xxx_close(struct net_device *ndev)
{
	struct ql3_adapter *qdev = netdev_priv(ndev);

	/*
	 * Wait for device to recover from a reset.
	 * (Rarely happens, but possible.)
	 */
	while (!test_bit(QL_ADAPTER_UP, &qdev->flags))
		msleep(50);

	ql_adapter_down(qdev, QL_DO_RESET);
	return 0;
}