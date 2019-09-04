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
struct enic {scalar_t__ flags; scalar_t__ uc_count; scalar_t__ mc_count; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_mc_unsync (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dev_uc_unsync (struct net_device*,int /*<<< orphan*/ *) ; 

void enic_reset_addr_lists(struct enic *enic)
{
	struct net_device *netdev = enic->netdev;

	__dev_uc_unsync(netdev, NULL);
	__dev_mc_unsync(netdev, NULL);

	enic->mc_count = 0;
	enic->uc_count = 0;
	enic->flags = 0;
}