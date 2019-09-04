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
struct mlxsw_sp_mr_vif {int vif_flags; } ;

/* Variables and functions */
 int MIFF_REGISTER ; 

__attribute__((used)) static bool mlxsw_sp_mr_vif6_is_regular(const struct mlxsw_sp_mr_vif *vif)
{
	return !(vif->vif_flags & MIFF_REGISTER);
}