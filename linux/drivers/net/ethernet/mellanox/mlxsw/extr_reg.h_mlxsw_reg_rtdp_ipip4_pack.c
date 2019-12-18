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
typedef  enum mlxsw_reg_rtdp_ipip_sip_check { ____Placeholder_mlxsw_reg_rtdp_ipip_sip_check } mlxsw_reg_rtdp_ipip_sip_check ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_rtdp_ipip_expected_gre_key_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rtdp_ipip_gre_key_check_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rtdp_ipip_ipv4_usip_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rtdp_ipip_irif_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rtdp_ipip_sip_check_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rtdp_ipip_type_check_set (char*,unsigned int) ; 

__attribute__((used)) static inline void
mlxsw_reg_rtdp_ipip4_pack(char *payload, u16 irif,
			  enum mlxsw_reg_rtdp_ipip_sip_check sip_check,
			  unsigned int type_check, bool gre_key_check,
			  u32 ipv4_usip, u32 expected_gre_key)
{
	mlxsw_reg_rtdp_ipip_irif_set(payload, irif);
	mlxsw_reg_rtdp_ipip_sip_check_set(payload, sip_check);
	mlxsw_reg_rtdp_ipip_type_check_set(payload, type_check);
	mlxsw_reg_rtdp_ipip_gre_key_check_set(payload, gre_key_check);
	mlxsw_reg_rtdp_ipip_ipv4_usip_set(payload, ipv4_usip);
	mlxsw_reg_rtdp_ipip_expected_gre_key_set(payload, expected_gre_key);
}