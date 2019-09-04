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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_hardware_context {scalar_t__ beacon_state; } ;
struct qlcnic_adapter {int drv_sds_rings; int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_LED_TEST ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  __QLCNIC_DIAG_RES_ALLOC ; 
 int /*<<< orphan*/  __QLCNIC_LED_ENABLE ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int qlcnic_config_led (struct qlcnic_adapter*,scalar_t__,scalar_t__) ; 
 int qlcnic_diag_alloc_res (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_diag_free_res (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qlcnic_get_beacon_state (struct qlcnic_adapter*) ; 
 int qlcnic_validate_beacon (struct qlcnic_adapter*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_82xx_store_beacon(struct qlcnic_adapter *adapter,
				    const char *buf, size_t len)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int err, drv_sds_rings = adapter->drv_sds_rings;
	u16 beacon;
	u8 b_state, b_rate;

	if (len != sizeof(u16))
		return -EINVAL;

	memcpy(&beacon, buf, sizeof(u16));
	err = qlcnic_validate_beacon(adapter, beacon, &b_state, &b_rate);
	if (err)
		return err;

	qlcnic_get_beacon_state(adapter);

	if (ahw->beacon_state == b_state)
		return len;

	rtnl_lock();
	if (!ahw->beacon_state) {
		if (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state)) {
			rtnl_unlock();
			return -EBUSY;
		}
	}

	if (test_bit(__QLCNIC_RESETTING, &adapter->state)) {
		err = -EIO;
		goto out;
	}

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) {
		err = qlcnic_diag_alloc_res(adapter->netdev, QLCNIC_LED_TEST);
		if (err)
			goto out;
		set_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state);
	}

	err = qlcnic_config_led(adapter, b_state, b_rate);
	if (!err) {
		err = len;
		ahw->beacon_state = b_state;
	}

	if (test_and_clear_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state))
		qlcnic_diag_free_res(adapter->netdev, drv_sds_rings);

out:
	if (!ahw->beacon_state)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);
	rtnl_unlock();

	return err;
}