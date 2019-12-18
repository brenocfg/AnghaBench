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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sbcm_dir_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sbcm_infi_max_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sbcm_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sbcm_max_buff_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sbcm_min_buff_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sbcm_pg_buff_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sbcm_pool_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbcm ; 

__attribute__((used)) static inline void mlxsw_reg_sbcm_pack(char *payload, u8 local_port, u8 pg_buff,
				       enum mlxsw_reg_sbxx_dir dir,
				       u32 min_buff, u32 max_buff,
				       bool infi_max, u8 pool)
{
	MLXSW_REG_ZERO(sbcm, payload);
	mlxsw_reg_sbcm_local_port_set(payload, local_port);
	mlxsw_reg_sbcm_pg_buff_set(payload, pg_buff);
	mlxsw_reg_sbcm_dir_set(payload, dir);
	mlxsw_reg_sbcm_min_buff_set(payload, min_buff);
	mlxsw_reg_sbcm_max_buff_set(payload, max_buff);
	mlxsw_reg_sbcm_infi_max_set(payload, infi_max);
	mlxsw_reg_sbcm_pool_set(payload, pool);
}