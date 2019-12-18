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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ionic_lif {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_LIF_SW_DEBUG_STATS ; 
 int /*<<< orphan*/  PRIV_F_SW_DBG_STATS ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ionic_get_priv_flags(struct net_device *netdev)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	u32 priv_flags = 0;

	if (test_bit(IONIC_LIF_SW_DEBUG_STATS, lif->state))
		priv_flags |= PRIV_F_SW_DBG_STATS;

	return priv_flags;
}