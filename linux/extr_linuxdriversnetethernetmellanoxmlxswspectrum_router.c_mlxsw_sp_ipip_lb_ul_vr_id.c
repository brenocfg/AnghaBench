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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_rif_ipip_lb {int /*<<< orphan*/  ul_vr_id; } ;

/* Variables and functions */

u16 mlxsw_sp_ipip_lb_ul_vr_id(const struct mlxsw_sp_rif_ipip_lb *lb_rif)
{
	return lb_rif->ul_vr_id;
}