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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_sfn_uc_tunnel_protocol { ____Placeholder_mlxsw_reg_sfn_uc_tunnel_protocol } mlxsw_reg_sfn_uc_tunnel_protocol ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_sfn_mac_fid_get (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfn_rec_mac_memcpy_from (char*,int,char*) ; 
 int mlxsw_reg_sfn_uc_tunnel_protocol_get (char*,int) ; 
 int mlxsw_reg_sfn_uc_tunnel_uip_lsb_get (char*,int) ; 
 int mlxsw_reg_sfn_uc_tunnel_uip_msb_get (char*,int) ; 

__attribute__((used)) static inline void
mlxsw_reg_sfn_uc_tunnel_unpack(char *payload, int rec_index, char *mac,
			       u16 *p_fid, u32 *p_uip,
			       enum mlxsw_reg_sfn_uc_tunnel_protocol *p_proto)
{
	u32 uip_msb, uip_lsb;

	mlxsw_reg_sfn_rec_mac_memcpy_from(payload, rec_index, mac);
	*p_fid = mlxsw_reg_sfn_mac_fid_get(payload, rec_index);
	uip_msb = mlxsw_reg_sfn_uc_tunnel_uip_msb_get(payload, rec_index);
	uip_lsb = mlxsw_reg_sfn_uc_tunnel_uip_lsb_get(payload, rec_index);
	*p_uip = uip_msb << 24 | uip_lsb;
	*p_proto = mlxsw_reg_sfn_uc_tunnel_protocol_get(payload, rec_index);
}