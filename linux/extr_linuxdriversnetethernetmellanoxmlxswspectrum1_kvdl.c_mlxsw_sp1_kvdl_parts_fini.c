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
struct mlxsw_sp1_kvdl {int /*<<< orphan*/ * parts; } ;

/* Variables and functions */
 int MLXSW_SP1_KVDL_PARTS_INFO_LEN ; 
 int /*<<< orphan*/  mlxsw_sp1_kvdl_part_fini (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp1_kvdl_parts_fini(struct mlxsw_sp1_kvdl *kvdl)
{
	int i;

	for (i = 0; i < MLXSW_SP1_KVDL_PARTS_INFO_LEN; i++)
		mlxsw_sp1_kvdl_part_fini(kvdl->parts[i]);
}