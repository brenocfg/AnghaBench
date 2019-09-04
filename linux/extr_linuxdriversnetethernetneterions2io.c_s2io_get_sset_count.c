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
struct s2io_nic {int /*<<< orphan*/  device_type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 131 
#define  ETH_SS_TEST 130 
 int S2IO_TEST_LEN ; 
#define  XFRAME_II_DEVICE 129 
 int XFRAME_II_STAT_LEN ; 
#define  XFRAME_I_DEVICE 128 
 int XFRAME_I_STAT_LEN ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int s2io_get_sset_count(struct net_device *dev, int sset)
{
	struct s2io_nic *sp = netdev_priv(dev);

	switch (sset) {
	case ETH_SS_TEST:
		return S2IO_TEST_LEN;
	case ETH_SS_STATS:
		switch (sp->device_type) {
		case XFRAME_I_DEVICE:
			return XFRAME_I_STAT_LEN;
		case XFRAME_II_DEVICE:
			return XFRAME_II_STAT_LEN;
		default:
			return 0;
		}
	default:
		return -EOPNOTSUPP;
	}
}