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
struct myri10ge_priv {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_ID_ACTIVE 129 
#define  ETHTOOL_ID_INACTIVE 128 
 int myri10ge_led (struct myri10ge_priv*,int) ; 
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
myri10ge_phys_id(struct net_device *netdev, enum ethtool_phys_id_state state)
{
	struct myri10ge_priv *mgp = netdev_priv(netdev);
	int rc;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		rc = myri10ge_led(mgp, 1);
		break;

	case ETHTOOL_ID_INACTIVE:
		rc =  myri10ge_led(mgp, 0);
		break;

	default:
		rc = -EINVAL;
	}

	return rc;
}