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
typedef  enum mlxsw_reg_sfdf_flush_type { ____Placeholder_mlxsw_reg_sfdf_flush_type } mlxsw_reg_sfdf_flush_type ;

/* Variables and functions */
 int MLXSW_REG_SFDF_FLUSH_PER_LAG_AND_FID ; 
 int MLXSW_REG_SFDF_FLUSH_PER_PORT_AND_FID ; 

__attribute__((used)) static enum mlxsw_reg_sfdf_flush_type mlxsw_sp_fdb_flush_type(bool lagged)
{
	return lagged ? MLXSW_REG_SFDF_FLUSH_PER_LAG_AND_FID :
			MLXSW_REG_SFDF_FLUSH_PER_PORT_AND_FID;
}