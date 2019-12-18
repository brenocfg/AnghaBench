#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct qlcnic_adapter {TYPE_3__* dcb; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cfg; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int dcb_capability; } ;
struct TYPE_5__ {TYPE_1__ capability; } ;

/* Variables and functions */
#define  DCB_CAP_ATTR_DCBX 134 
#define  DCB_CAP_ATTR_GSP 133 
#define  DCB_CAP_ATTR_PFC 132 
#define  DCB_CAP_ATTR_PFC_TCS 131 
#define  DCB_CAP_ATTR_PG 130 
#define  DCB_CAP_ATTR_PG_TCS 129 
#define  DCB_CAP_ATTR_UP2TC 128 
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 qlcnic_dcb_get_capability(struct net_device *netdev, int capid,
				    u8 *cap)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);

	if (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		return 1;

	switch (capid) {
	case DCB_CAP_ATTR_PG:
	case DCB_CAP_ATTR_UP2TC:
	case DCB_CAP_ATTR_PFC:
	case DCB_CAP_ATTR_GSP:
		*cap = true;
		break;
	case DCB_CAP_ATTR_PG_TCS:
	case DCB_CAP_ATTR_PFC_TCS:
		*cap = 0x80;	/* 8 priorities for PGs */
		break;
	case DCB_CAP_ATTR_DCBX:
		*cap = adapter->dcb->cfg->capability.dcb_capability;
		break;
	default:
		*cap = false;
	}

	return 0;
}