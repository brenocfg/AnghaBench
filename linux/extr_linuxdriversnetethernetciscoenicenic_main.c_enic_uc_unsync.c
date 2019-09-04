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
struct enic {int /*<<< orphan*/  uc_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  enic_dev_del_addr (struct enic*,int /*<<< orphan*/  const*) ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enic_uc_unsync(struct net_device *netdev, const u8 *uc_addr)
{
	struct enic *enic = netdev_priv(netdev);

	enic_dev_del_addr(enic, uc_addr);
	enic->uc_count--;

	return 0;
}