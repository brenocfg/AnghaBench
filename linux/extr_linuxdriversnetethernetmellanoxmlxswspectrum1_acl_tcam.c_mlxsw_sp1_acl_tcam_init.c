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
struct mlxsw_sp_acl_tcam {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mlxsw_sp1_acl_tcam_init(struct mlxsw_sp *mlxsw_sp, void *priv,
				   struct mlxsw_sp_acl_tcam *tcam)
{
	return 0;
}