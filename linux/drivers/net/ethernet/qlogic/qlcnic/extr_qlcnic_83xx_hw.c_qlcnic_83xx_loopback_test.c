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
typedef  void* u8 ;
struct qlcnic_hardware_context {scalar_t__ op_mode; scalar_t__ has_link_events; scalar_t__ linkup; } ;
struct qlcnic_adapter {void* drv_tx_rings; void* drv_sds_rings; int /*<<< orphan*/  state; struct qlcnic_hardware_context* ahw; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTSUPP ; 
 int ETIMEDOUT ; 
 void* QLCNIC_ILB_MODE ; 
 int /*<<< orphan*/  QLCNIC_LOOPBACK_TEST ; 
 scalar_t__ QLCNIC_NON_PRIV_FUNC ; 
 int /*<<< orphan*/  QLC_83XX_LB_MSLEEP_COUNT ; 
 int /*<<< orphan*/  QLC_83XX_LB_WAIT_COUNT ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  qlcnic_83xx_clear_lb_mode (struct qlcnic_adapter*,void*) ; 
 int qlcnic_83xx_diag_alloc_res (struct net_device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  qlcnic_83xx_diag_free_res (struct net_device*,void*) ; 
 int qlcnic_83xx_set_lb_mode (struct qlcnic_adapter*,void*) ; 
 int qlcnic_do_lb_test (struct qlcnic_adapter*,void*) ; 
 scalar_t__ qlcnic_get_diag_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_release_diag_lock (struct qlcnic_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_83xx_loopback_test(struct net_device *netdev, u8 mode)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	u8 drv_sds_rings = adapter->drv_sds_rings;
	u8 drv_tx_rings = adapter->drv_tx_rings;
	int ret = 0, loop = 0;

	if (ahw->op_mode == QLCNIC_NON_PRIV_FUNC) {
		netdev_warn(netdev,
			    "Loopback test not supported in non privileged mode\n");
		return -ENOTSUPP;
	}

	if (test_bit(__QLCNIC_RESETTING, &adapter->state)) {
		netdev_info(netdev, "Device is resetting\n");
		return -EBUSY;
	}

	if (qlcnic_get_diag_lock(adapter)) {
		netdev_info(netdev, "Device is in diagnostics mode\n");
		return -EBUSY;
	}

	netdev_info(netdev, "%s loopback test in progress\n",
		    mode == QLCNIC_ILB_MODE ? "internal" : "external");

	ret = qlcnic_83xx_diag_alloc_res(netdev, QLCNIC_LOOPBACK_TEST,
					 drv_sds_rings);
	if (ret)
		goto fail_diag_alloc;

	ret = qlcnic_83xx_set_lb_mode(adapter, mode);
	if (ret)
		goto free_diag_res;

	/* Poll for link up event before running traffic */
	do {
		msleep(QLC_83XX_LB_MSLEEP_COUNT);

		if (test_bit(__QLCNIC_RESETTING, &adapter->state)) {
			netdev_info(netdev,
				    "Device is resetting, free LB test resources\n");
			ret = -EBUSY;
			goto free_diag_res;
		}
		if (loop++ > QLC_83XX_LB_WAIT_COUNT) {
			netdev_info(netdev,
				    "Firmware didn't sent link up event to loopback request\n");
			ret = -ETIMEDOUT;
			qlcnic_83xx_clear_lb_mode(adapter, mode);
			goto free_diag_res;
		}
	} while ((adapter->ahw->linkup && ahw->has_link_events) != 1);

	ret = qlcnic_do_lb_test(adapter, mode);

	qlcnic_83xx_clear_lb_mode(adapter, mode);

free_diag_res:
	qlcnic_83xx_diag_free_res(netdev, drv_sds_rings);

fail_diag_alloc:
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;
	qlcnic_release_diag_lock(adapter);
	return ret;
}