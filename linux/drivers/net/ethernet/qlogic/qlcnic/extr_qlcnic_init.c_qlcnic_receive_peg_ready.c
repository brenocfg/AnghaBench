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
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ PHAN_PEG_RCV_INITIALIZED ; 
 int /*<<< orphan*/  QLCNIC_RCVPEG_CHECK_DELAY ; 
 int QLCNIC_RCVPEG_CHECK_RETRY_COUNT ; 
 int /*<<< orphan*/  QLCNIC_RCVPEG_STATE ; 
 scalar_t__ QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlcnic_receive_peg_ready(struct qlcnic_adapter *adapter)
{
	u32 val;
	int retries = QLCNIC_RCVPEG_CHECK_RETRY_COUNT;

	do {
		val = QLC_SHARED_REG_RD32(adapter, QLCNIC_RCVPEG_STATE);

		if (val == PHAN_PEG_RCV_INITIALIZED)
			return 0;

		msleep(QLCNIC_RCVPEG_CHECK_DELAY);

	} while (--retries);

	dev_err(&adapter->pdev->dev, "Receive Peg initialization not complete, state: 0x%x.\n",
		val);
	return -EIO;
}