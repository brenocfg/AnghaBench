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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  QLCDB (struct qlcnic_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QLCNIC_CRB_DEV_NPAR_STATE ; 
 int /*<<< orphan*/  QLCNIC_DEV_NPAR_OPER ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_api_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_api_unlock (struct qlcnic_adapter*) ; 

__attribute__((used)) static void
qlcnic_dev_set_npar_ready(struct qlcnic_adapter *adapter)
{
	if (qlcnic_api_lock(adapter))
		return;

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_NPAR_STATE,
			    QLCNIC_DEV_NPAR_OPER);
	QLCDB(adapter, DRV, "NPAR operational state set\n");

	qlcnic_api_unlock(adapter);
}