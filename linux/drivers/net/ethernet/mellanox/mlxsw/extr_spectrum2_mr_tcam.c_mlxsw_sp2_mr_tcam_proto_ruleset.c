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
struct mlxsw_sp_acl_ruleset {int dummy; } ;
struct mlxsw_sp2_mr_tcam {struct mlxsw_sp_acl_ruleset* ruleset6; struct mlxsw_sp_acl_ruleset* ruleset4; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 

__attribute__((used)) static struct mlxsw_sp_acl_ruleset *
mlxsw_sp2_mr_tcam_proto_ruleset(struct mlxsw_sp2_mr_tcam *mr_tcam,
				enum mlxsw_sp_l3proto proto)
{
	switch (proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		return mr_tcam->ruleset4;
	case MLXSW_SP_L3_PROTO_IPV6:
		return mr_tcam->ruleset6;
	}
	return NULL;
}