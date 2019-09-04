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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  MLXSW_AFA_MCROUTER_CODE ; 
 int /*<<< orphan*/  MLXSW_AFA_MCROUTER_RPF_ACTION_TRAP ; 
 int /*<<< orphan*/  MLXSW_AFA_MCROUTER_SIZE ; 
 int PTR_ERR (char*) ; 
 char* mlxsw_afa_block_append_action (struct mlxsw_afa_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_mcrouter_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mlxsw_afa_block_append_mcrouter(struct mlxsw_afa_block *block,
				    u16 expected_irif, u16 min_mtu,
				    bool rmid_valid, u32 kvdl_index)
{
	char *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_MCROUTER_CODE,
						  MLXSW_AFA_MCROUTER_SIZE);
	if (IS_ERR(act))
		return PTR_ERR(act);
	mlxsw_afa_mcrouter_pack(act, MLXSW_AFA_MCROUTER_RPF_ACTION_TRAP,
				expected_irif, min_mtu, rmid_valid, kvdl_index);
	return 0;
}