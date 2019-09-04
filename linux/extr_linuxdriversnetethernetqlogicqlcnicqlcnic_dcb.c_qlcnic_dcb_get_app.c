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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_adapter {TYPE_1__* dcb; } ;
struct net_device {int dummy; } ;
struct dcb_app {int /*<<< orphan*/  protocol; int /*<<< orphan*/  selector; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 int dcb_getapp (struct net_device*,struct dcb_app*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_dcb_get_app(struct net_device *netdev, u8 idtype, u16 id)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct dcb_app app = {
				.selector = idtype,
				.protocol = id,
			     };

	if (!test_bit(QLCNIC_DCB_STATE, &adapter->dcb->state))
		return -EINVAL;

	return dcb_getapp(netdev, &app);
}