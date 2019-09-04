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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_disable_vxlan_hw (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_disable_vxlan_offloads (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_disable_vxlan_accel(struct xgbe_prv_data *pdata)
{
	xgbe_disable_vxlan_offloads(pdata);

	xgbe_disable_vxlan_hw(pdata);
}