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
typedef  enum mlxsw_reg_rauht_op { ____Placeholder_mlxsw_reg_rauht_op } mlxsw_reg_rauht_op ;

/* Variables and functions */
 int MLXSW_REG_RAUHT_OP_WRITE_ADD ; 
 int MLXSW_REG_RAUHT_OP_WRITE_DELETE ; 

__attribute__((used)) static enum mlxsw_reg_rauht_op mlxsw_sp_rauht_op(bool adding)
{
	return adding ? MLXSW_REG_RAUHT_OP_WRITE_ADD :
			MLXSW_REG_RAUHT_OP_WRITE_DELETE;
}