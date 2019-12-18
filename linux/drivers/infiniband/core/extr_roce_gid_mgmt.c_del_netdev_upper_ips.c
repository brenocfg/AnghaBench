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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _roce_del_all_netdev_gids ; 
 int /*<<< orphan*/  handle_netdev_upper (struct ib_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void del_netdev_upper_ips(struct ib_device *ib_dev, u8 port,
				 struct net_device *rdma_ndev, void *cookie)
{
	handle_netdev_upper(ib_dev, port, cookie, _roce_del_all_netdev_gids);
}