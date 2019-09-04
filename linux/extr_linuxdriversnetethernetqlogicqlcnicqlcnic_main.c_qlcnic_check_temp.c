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
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_ASIC_TEMP ; 
 scalar_t__ QLCNIC_TEMP_NORMAL ; 
 scalar_t__ QLCNIC_TEMP_PANIC ; 
 scalar_t__ QLCNIC_TEMP_WARN ; 
 scalar_t__ QLCRDX (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_ASIC_TEMP ; 
 scalar_t__ QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_get_temp_state (scalar_t__) ; 
 scalar_t__ qlcnic_get_temp_val (scalar_t__) ; 

int qlcnic_check_temp(struct qlcnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	u32 temp_state, temp_val, temp = 0;
	int rv = 0;

	if (qlcnic_83xx_check(adapter))
		temp = QLCRDX(adapter->ahw, QLC_83XX_ASIC_TEMP);

	if (qlcnic_82xx_check(adapter))
		temp = QLC_SHARED_REG_RD32(adapter, QLCNIC_ASIC_TEMP);

	temp_state = qlcnic_get_temp_state(temp);
	temp_val = qlcnic_get_temp_val(temp);

	if (temp_state == QLCNIC_TEMP_PANIC) {
		dev_err(&netdev->dev,
		       "Device temperature %d degrees C exceeds"
		       " maximum allowed. Hardware has been shut down.\n",
		       temp_val);
		rv = 1;
	} else if (temp_state == QLCNIC_TEMP_WARN) {
		if (adapter->ahw->temp == QLCNIC_TEMP_NORMAL) {
			dev_err(&netdev->dev,
			       "Device temperature %d degrees C "
			       "exceeds operating range."
			       " Immediate action needed.\n",
			       temp_val);
		}
	} else {
		if (adapter->ahw->temp == QLCNIC_TEMP_WARN) {
			dev_info(&netdev->dev,
			       "Device temperature is now %d degrees C"
			       " in normal range.\n", temp_val);
		}
	}
	adapter->ahw->temp = temp_state;
	return rv;
}