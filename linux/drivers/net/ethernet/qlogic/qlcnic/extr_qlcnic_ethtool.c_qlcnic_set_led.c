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
struct qlcnic_adapter {int drv_sds_rings; int /*<<< orphan*/  state; TYPE_3__* pdev; TYPE_2__* nic_ops; TYPE_1__* ahw; } ;
struct net_device {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* config_led ) (struct qlcnic_adapter*,int,int) ;} ;
struct TYPE_4__ {scalar_t__ op_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_ID_ACTIVE 129 
#define  ETHTOOL_ID_INACTIVE 128 
 int /*<<< orphan*/  QLCNIC_LED_TEST ; 
 scalar_t__ QLCNIC_NON_PRIV_FUNC ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  __QLCNIC_DIAG_RES_ALLOC ; 
 int /*<<< orphan*/  __QLCNIC_LED_ENABLE ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_set_led (struct net_device*,int) ; 
 int /*<<< orphan*/  qlcnic_diag_alloc_res (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_diag_free_res (struct net_device*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct qlcnic_adapter*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct qlcnic_adapter*,int,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_set_led(struct net_device *dev,
			  enum ethtool_phys_id_state state)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	int drv_sds_rings = adapter->drv_sds_rings;
	int err = -EIO, active = 1;

	if (qlcnic_83xx_check(adapter))
		return qlcnic_83xx_set_led(dev, state);

	if (adapter->ahw->op_mode == QLCNIC_NON_PRIV_FUNC) {
		netdev_warn(dev, "LED test not supported for non "
				"privilege function\n");
		return -EOPNOTSUPP;
	}

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		if (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state))
			return -EBUSY;

		if (test_bit(__QLCNIC_RESETTING, &adapter->state))
			break;

		if (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) {
			if (qlcnic_diag_alloc_res(dev, QLCNIC_LED_TEST))
				break;
			set_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state);
		}

		if (adapter->nic_ops->config_led(adapter, 1, 0xf) == 0) {
			err = 0;
			break;
		}

		dev_err(&adapter->pdev->dev,
			"Failed to set LED blink state.\n");
		break;

	case ETHTOOL_ID_INACTIVE:
		active = 0;

		if (test_bit(__QLCNIC_RESETTING, &adapter->state))
			break;

		if (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) {
			if (qlcnic_diag_alloc_res(dev, QLCNIC_LED_TEST))
				break;
			set_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state);
		}

		if (adapter->nic_ops->config_led(adapter, 0, 0xf))
			dev_err(&adapter->pdev->dev,
				"Failed to reset LED blink state.\n");

		break;

	default:
		return -EINVAL;
	}

	if (test_and_clear_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state))
		qlcnic_diag_free_res(dev, drv_sds_rings);

	if (!active || err)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);

	return err;
}