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
struct mlxsw_sp2_kvdl {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp2_kvdl_parts_init (struct mlxsw_sp*,struct mlxsw_sp2_kvdl*) ; 

__attribute__((used)) static int mlxsw_sp2_kvdl_init(struct mlxsw_sp *mlxsw_sp, void *priv)
{
	struct mlxsw_sp2_kvdl *kvdl = priv;

	return mlxsw_sp2_kvdl_parts_init(mlxsw_sp, kvdl);
}