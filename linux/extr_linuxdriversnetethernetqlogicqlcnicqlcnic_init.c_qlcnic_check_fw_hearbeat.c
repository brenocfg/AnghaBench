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
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {scalar_t__ heartbeat; } ;

/* Variables and functions */
 scalar_t__ EIO ; 
 int QLCNIC_HEARTBEAT_CHECK_RETRY_COUNT ; 
 int /*<<< orphan*/  QLCNIC_HEARTBEAT_PERIOD_MSECS ; 
 int /*<<< orphan*/  QLCNIC_PEG_ALIVE_COUNTER ; 
 scalar_t__ QLCNIC_RCODE_SUCCESS ; 
 void* QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlcnic_check_fw_hearbeat(struct qlcnic_adapter *adapter)
{
	u32 heartbeat, ret = -EIO;
	int retries = QLCNIC_HEARTBEAT_CHECK_RETRY_COUNT;

	adapter->heartbeat = QLC_SHARED_REG_RD32(adapter,
						 QLCNIC_PEG_ALIVE_COUNTER);

	do {
		msleep(QLCNIC_HEARTBEAT_PERIOD_MSECS);
		heartbeat = QLC_SHARED_REG_RD32(adapter,
						QLCNIC_PEG_ALIVE_COUNTER);
		if (heartbeat != adapter->heartbeat) {
			ret = QLCNIC_RCODE_SUCCESS;
			break;
		}
	} while (--retries);

	return ret;
}