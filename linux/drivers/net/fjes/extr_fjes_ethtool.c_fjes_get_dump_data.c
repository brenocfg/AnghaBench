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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  trace_size; scalar_t__ trace; } ;
struct fjes_hw {TYPE_1__ hw_info; } ;
struct fjes_adapter {struct fjes_hw hw; } ;
struct ethtool_dump {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct fjes_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fjes_get_dump_data(struct net_device *netdev,
			      struct ethtool_dump *dump, void *buf)
{
	struct fjes_adapter *adapter = netdev_priv(netdev);
	struct fjes_hw *hw = &adapter->hw;
	int ret = 0;

	if (hw->hw_info.trace)
		memcpy(buf, hw->hw_info.trace, hw->hw_info.trace_size);
	else
		ret = -EPERM;

	return ret;
}