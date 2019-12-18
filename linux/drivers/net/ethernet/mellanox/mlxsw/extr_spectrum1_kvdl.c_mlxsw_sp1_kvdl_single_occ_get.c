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
typedef  int /*<<< orphan*/  u64 ;
struct mlxsw_sp1_kvdl_part {int dummy; } ;
struct mlxsw_sp1_kvdl {struct mlxsw_sp1_kvdl_part** parts; } ;

/* Variables and functions */
 size_t MLXSW_SP1_KVDL_PART_ID_SINGLE ; 
 int /*<<< orphan*/  mlxsw_sp1_kvdl_part_occ (struct mlxsw_sp1_kvdl_part*) ; 

__attribute__((used)) static u64 mlxsw_sp1_kvdl_single_occ_get(void *priv)
{
	const struct mlxsw_sp1_kvdl *kvdl = priv;
	struct mlxsw_sp1_kvdl_part *part;

	part = kvdl->parts[MLXSW_SP1_KVDL_PART_ID_SINGLE];
	return mlxsw_sp1_kvdl_part_occ(part);
}