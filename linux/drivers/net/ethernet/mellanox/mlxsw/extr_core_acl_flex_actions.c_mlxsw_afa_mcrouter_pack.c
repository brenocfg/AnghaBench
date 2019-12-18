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
typedef  enum mlxsw_afa_mrouter_vrmid { ____Placeholder_mlxsw_afa_mrouter_vrmid } mlxsw_afa_mrouter_vrmid ;
typedef  enum mlxsw_afa_mcrouter_rpf_action { ____Placeholder_mlxsw_afa_mcrouter_rpf_action } mlxsw_afa_mcrouter_rpf_action ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_mcrouter_expected_irif_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_mcrouter_min_mtu_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_mcrouter_rigr_rmid_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_mcrouter_rpf_action_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_afa_mcrouter_vrmid_set (char*,int) ; 

__attribute__((used)) static inline void
mlxsw_afa_mcrouter_pack(char *payload,
			enum mlxsw_afa_mcrouter_rpf_action rpf_action,
			u16 expected_irif, u16 min_mtu,
			enum mlxsw_afa_mrouter_vrmid vrmid, u32 rigr_rmid_index)

{
	mlxsw_afa_mcrouter_rpf_action_set(payload, rpf_action);
	mlxsw_afa_mcrouter_expected_irif_set(payload, expected_irif);
	mlxsw_afa_mcrouter_min_mtu_set(payload, min_mtu);
	mlxsw_afa_mcrouter_vrmid_set(payload, vrmid);
	mlxsw_afa_mcrouter_rigr_rmid_index_set(payload, rigr_rmid_index);
}