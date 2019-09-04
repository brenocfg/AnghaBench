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
struct xgbe_prv_data {scalar_t__ vxlan_force_disable; int /*<<< orphan*/  vxlan_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_enable_vxlan_hw (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_vxlan_offloads (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_enable_vxlan_accel(struct xgbe_prv_data *pdata)
{
	/* VXLAN acceleration desired? */
	if (!pdata->vxlan_features)
		return;

	/* VXLAN acceleration possible? */
	if (pdata->vxlan_force_disable)
		return;

	xgbe_enable_vxlan_hw(pdata);

	xgbe_enable_vxlan_offloads(pdata);
}