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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int MLXSW_REG_RALST_BIN_COUNT ; 
 int /*<<< orphan*/  MLXSW_REG_RALST_BIN_NO_CHILD ; 
 int MLXSW_REG_RALST_BIN_OFFSET ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ralst_root_bin_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralst_tree_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ralst ; 

__attribute__((used)) static inline void mlxsw_reg_ralst_pack(char *payload, u8 root_bin, u8 tree_id)
{
	MLXSW_REG_ZERO(ralst, payload);

	/* Initialize all bins to have no left or right child */
	memset(payload + MLXSW_REG_RALST_BIN_OFFSET,
	       MLXSW_REG_RALST_BIN_NO_CHILD, MLXSW_REG_RALST_BIN_COUNT * 2);

	mlxsw_reg_ralst_root_bin_set(payload, root_bin);
	mlxsw_reg_ralst_tree_id_set(payload, tree_id);
}