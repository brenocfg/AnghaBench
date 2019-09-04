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
struct ql_adapter {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ql_queue_asic_error (struct ql_adapter*) ; 

__attribute__((used)) static void qlge_tx_timeout(struct net_device *ndev)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	ql_queue_asic_error(qdev);
}