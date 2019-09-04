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
struct mlxsw_sp_mr_route {TYPE_1__* mfc; } ;
struct TYPE_2__ {int /*<<< orphan*/  mfc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFC_OFFLOAD ; 

__attribute__((used)) static void mlxsw_sp_mr_mfc_offload_set(struct mlxsw_sp_mr_route *mr_route,
					bool offload)
{
	if (offload)
		mr_route->mfc->mfc_flags |= MFC_OFFLOAD;
	else
		mr_route->mfc->mfc_flags &= ~MFC_OFFLOAD;
}