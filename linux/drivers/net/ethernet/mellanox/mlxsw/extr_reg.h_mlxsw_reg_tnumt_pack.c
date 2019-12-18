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
typedef  enum mlxsw_reg_tnumt_tunnel_port { ____Placeholder_mlxsw_reg_tnumt_tunnel_port } mlxsw_reg_tnumt_tunnel_port ;
typedef  enum mlxsw_reg_tnumt_record_type { ____Placeholder_mlxsw_reg_tnumt_record_type } mlxsw_reg_tnumt_record_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_tnumt_next_underlay_mc_ptr_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tnumt_record_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tnumt_record_type_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_tnumt_tunnel_port_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_tnumt_underlay_mc_ptr_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tnumt_vnext_set (char*,int) ; 
 int /*<<< orphan*/  tnumt ; 

__attribute__((used)) static inline void mlxsw_reg_tnumt_pack(char *payload,
					enum mlxsw_reg_tnumt_record_type type,
					enum mlxsw_reg_tnumt_tunnel_port tport,
					u32 underlay_mc_ptr, bool vnext,
					u32 next_underlay_mc_ptr,
					u8 record_size)
{
	MLXSW_REG_ZERO(tnumt, payload);
	mlxsw_reg_tnumt_record_type_set(payload, type);
	mlxsw_reg_tnumt_tunnel_port_set(payload, tport);
	mlxsw_reg_tnumt_underlay_mc_ptr_set(payload, underlay_mc_ptr);
	mlxsw_reg_tnumt_vnext_set(payload, vnext);
	mlxsw_reg_tnumt_next_underlay_mc_ptr_set(payload, next_underlay_mc_ptr);
	mlxsw_reg_tnumt_record_size_set(payload, record_size);
}