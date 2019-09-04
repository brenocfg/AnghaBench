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
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {scalar_t__ op_mode; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_SRIOV_PF_FUNC ; 

__attribute__((used)) static inline bool qlcnic_sriov_pf_check(struct qlcnic_adapter *adapter)
{
	return (adapter->ahw->op_mode == QLCNIC_SRIOV_PF_FUNC) ? true : false;
}