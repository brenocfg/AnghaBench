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
struct TYPE_2__ {int /*<<< orphan*/  (* disable_vxlan ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {scalar_t__ vxlan_port; scalar_t__ vxlan_port_set; TYPE_1__ hw_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_disable_vxlan_hw(struct xgbe_prv_data *pdata)
{
	if (!pdata->vxlan_port_set)
		return;

	pdata->hw_if.disable_vxlan(pdata);

	pdata->vxlan_port_set = 0;
	pdata->vxlan_port = 0;
}