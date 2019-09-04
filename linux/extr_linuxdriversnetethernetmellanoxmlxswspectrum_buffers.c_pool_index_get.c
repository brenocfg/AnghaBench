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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;

/* Variables and functions */
 int MLXSW_REG_SBXX_DIR_EGRESS ; 
 scalar_t__ MLXSW_SP_SB_POOL_COUNT ; 

__attribute__((used)) static u16 pool_index_get(u8 pool, enum mlxsw_reg_sbxx_dir dir)
{
	u16 pool_index;

	pool_index = pool;
	if (dir == MLXSW_REG_SBXX_DIR_EGRESS)
		pool_index += MLXSW_SP_SB_POOL_COUNT;
	return pool_index;
}