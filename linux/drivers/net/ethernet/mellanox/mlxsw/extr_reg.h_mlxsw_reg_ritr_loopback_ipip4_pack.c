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
typedef  enum mlxsw_reg_ritr_loopback_ipip_type { ____Placeholder_mlxsw_reg_ritr_loopback_ipip_type } mlxsw_reg_ritr_loopback_ipip_type ;
typedef  enum mlxsw_reg_ritr_loopback_ipip_options { ____Placeholder_mlxsw_reg_ritr_loopback_ipip_options } mlxsw_reg_ritr_loopback_ipip_options ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_RITR_LOOPBACK_PROTOCOL_IPIP_IPV4 ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_loopback_ipip_common_pack (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_loopback_ipip_usip4_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_loopback_protocol_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlxsw_reg_ritr_loopback_ipip4_pack(char *payload,
			    enum mlxsw_reg_ritr_loopback_ipip_type ipip_type,
			    enum mlxsw_reg_ritr_loopback_ipip_options options,
			    u16 uvr_id, u16 underlay_rif, u32 usip, u32 gre_key)
{
	mlxsw_reg_ritr_loopback_protocol_set(payload,
				    MLXSW_REG_RITR_LOOPBACK_PROTOCOL_IPIP_IPV4);
	mlxsw_reg_ritr_loopback_ipip_common_pack(payload, ipip_type, options,
						 uvr_id, underlay_rif, gre_key);
	mlxsw_reg_ritr_loopback_ipip_usip4_set(payload, usip);
}