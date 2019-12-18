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
struct qlcnic_adapter {int /*<<< orphan*/  ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CLR_OWNER ; 
 int /*<<< orphan*/  QLCNIC_FW_MBX_CTRL ; 
 int /*<<< orphan*/  QLCNIC_HOST_MBX_CTRL ; 
 int /*<<< orphan*/  QLCNIC_SET_OWNER ; 
 int /*<<< orphan*/  QLCWRX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qlcnic_83xx_signal_mbx_cmd(struct qlcnic_adapter *adapter,
					      u8 issue_cmd)
{
	if (issue_cmd)
		QLCWRX(adapter->ahw, QLCNIC_HOST_MBX_CTRL, QLCNIC_SET_OWNER);
	else
		QLCWRX(adapter->ahw, QLCNIC_FW_MBX_CTRL, QLCNIC_CLR_OWNER);
}