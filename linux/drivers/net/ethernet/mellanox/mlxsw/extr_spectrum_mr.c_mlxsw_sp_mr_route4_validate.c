#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mr_mfc {int dummy; } ;
struct mlxsw_sp_mr_table {TYPE_2__* mlxsw_sp; } ;
struct mfc_cache {scalar_t__ mfc_origin; scalar_t__ mfc_mcastgrp; } ;
struct TYPE_4__ {TYPE_1__* bus_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mlxsw_sp_mr_route4_validate(const struct mlxsw_sp_mr_table *mr_table,
			    const struct mr_mfc *c)
{
	struct mfc_cache *mfc = (struct mfc_cache *) c;

	/* If the route is a (*,*) route, abort, as these kind of routes are
	 * used for proxy routes.
	 */
	if (mfc->mfc_origin == htonl(INADDR_ANY) &&
	    mfc->mfc_mcastgrp == htonl(INADDR_ANY)) {
		dev_warn(mr_table->mlxsw_sp->bus_info->dev,
			 "Offloading proxy routes is not supported.\n");
		return false;
	}
	return true;
}