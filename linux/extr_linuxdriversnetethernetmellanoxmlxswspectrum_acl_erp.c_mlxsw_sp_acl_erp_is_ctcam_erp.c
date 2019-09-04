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
struct TYPE_2__ {int ctcam; } ;
struct mlxsw_sp_acl_erp {TYPE_1__ key; } ;

/* Variables and functions */

bool mlxsw_sp_acl_erp_is_ctcam_erp(const struct mlxsw_sp_acl_erp *erp)
{
	return erp->key.ctcam;
}