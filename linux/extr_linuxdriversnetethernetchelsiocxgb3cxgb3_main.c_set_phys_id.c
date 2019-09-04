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
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int /*<<< orphan*/  A_T3DBG_GPIO_EN ; 
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  F_GPIO0_OUT_VAL ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_phys_id(struct net_device *dev,
		       enum ethtool_phys_id_state state)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		return 1;	/* cycle on/off once per second */

	case ETHTOOL_ID_OFF:
		t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, F_GPIO0_OUT_VAL, 0);
		break;

	case ETHTOOL_ID_ON:
	case ETHTOOL_ID_INACTIVE:
		t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, F_GPIO0_OUT_VAL,
			 F_GPIO0_OUT_VAL);
	}

	return 0;
}