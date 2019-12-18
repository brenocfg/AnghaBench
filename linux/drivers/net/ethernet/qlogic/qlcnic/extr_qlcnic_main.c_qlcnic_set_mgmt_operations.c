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
struct qlcnic_adapter {int flags; TYPE_1__* ahw; } ;
struct TYPE_2__ {scalar_t__ op_mode; } ;

/* Variables and functions */
 int QLCNIC_ESWITCH_ENABLED ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
 int /*<<< orphan*/  qlcnic_dev_set_npar_ready (struct qlcnic_adapter*) ; 
 int qlcnic_reset_npar_config (struct qlcnic_adapter*) ; 
 int qlcnic_set_default_offload_settings (struct qlcnic_adapter*) ; 

__attribute__((used)) static int
qlcnic_set_mgmt_operations(struct qlcnic_adapter *adapter)
{
	int err;

	if (!(adapter->flags & QLCNIC_ESWITCH_ENABLED) ||
	    adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		return 0;

	err = qlcnic_set_default_offload_settings(adapter);
	if (err)
		return err;

	err = qlcnic_reset_npar_config(adapter);
	if (err)
		return err;

	qlcnic_dev_set_npar_ready(adapter);

	return err;
}