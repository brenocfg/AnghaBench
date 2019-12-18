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
struct mlxsw_sp1_kvdl {int /*<<< orphan*/ * parts; } ;

/* Variables and functions */
 int MLXSW_SP1_KVDL_PARTS_INFO_LEN ; 
 scalar_t__ mlxsw_sp1_kvdl_part_occ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 mlxsw_sp1_kvdl_occ_get(void *priv)
{
	const struct mlxsw_sp1_kvdl *kvdl = priv;
	u64 occ = 0;
	int i;

	for (i = 0; i < MLXSW_SP1_KVDL_PARTS_INFO_LEN; i++)
		occ += mlxsw_sp1_kvdl_part_occ(kvdl->parts[i]);

	return occ;
}