#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vifi_t ;
struct mlxsw_sp_mr_route {TYPE_3__* mfc; } ;
struct TYPE_4__ {int* ttls; } ;
struct TYPE_5__ {TYPE_1__ res; } ;
struct TYPE_6__ {size_t mfc_parent; TYPE_2__ mfc_un; } ;

/* Variables and functions */

__attribute__((used)) static bool
mlxsw_sp_mr_route_ivif_in_evifs(const struct mlxsw_sp_mr_route *mr_route)
{
	vifi_t ivif = mr_route->mfc->mfc_parent;

	return mr_route->mfc->mfc_un.res.ttls[ivif] != 255;
}