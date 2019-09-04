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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_svfa_mt { ____Placeholder_mlxsw_reg_svfa_mt } mlxsw_reg_svfa_mt ;

/* Variables and functions */
 int MLXSW_REG_SVFA_MT_VID_TO_FID ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_svfa_fid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_svfa_local_port_set (char*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_reg_svfa_mapping_table_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_svfa_swid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_svfa_v_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_svfa_vid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svfa ; 

__attribute__((used)) static inline void mlxsw_reg_svfa_pack(char *payload, u8 local_port,
				       enum mlxsw_reg_svfa_mt mt, bool valid,
				       u16 fid, u16 vid)
{
	MLXSW_REG_ZERO(svfa, payload);
	local_port = mt == MLXSW_REG_SVFA_MT_VID_TO_FID ? 0 : local_port;
	mlxsw_reg_svfa_swid_set(payload, 0);
	mlxsw_reg_svfa_local_port_set(payload, local_port);
	mlxsw_reg_svfa_mapping_table_set(payload, mt);
	mlxsw_reg_svfa_v_set(payload, valid);
	mlxsw_reg_svfa_fid_set(payload, fid);
	mlxsw_reg_svfa_vid_set(payload, vid);
}