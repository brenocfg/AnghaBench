#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct parman_item {int /*<<< orphan*/  index; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr4; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr4; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr4; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr4; } ;
struct mlxsw_sp_mr_route_key {int proto; TYPE_4__ source_mask; TYPE_3__ source; TYPE_2__ group_mask; TYPE_1__ group; int /*<<< orphan*/  vrid; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_RMFT2_IRIF_MASK_IGNORE ; 
 int MLXSW_REG_RMFT2_LEN ; 
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 
 int /*<<< orphan*/  mlxsw_afa_block_first_set (struct mlxsw_afa_block*) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_ipv4_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_ipv6_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmft2 ; 

__attribute__((used)) static int mlxsw_sp1_mr_tcam_route_replace(struct mlxsw_sp *mlxsw_sp,
					   struct parman_item *parman_item,
					   struct mlxsw_sp_mr_route_key *key,
					   struct mlxsw_afa_block *afa_block)
{
	char rmft2_pl[MLXSW_REG_RMFT2_LEN];

	switch (key->proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		mlxsw_reg_rmft2_ipv4_pack(rmft2_pl, true, parman_item->index,
					  key->vrid,
					  MLXSW_REG_RMFT2_IRIF_MASK_IGNORE, 0,
					  ntohl(key->group.addr4),
					  ntohl(key->group_mask.addr4),
					  ntohl(key->source.addr4),
					  ntohl(key->source_mask.addr4),
					  mlxsw_afa_block_first_set(afa_block));
		break;
	case MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_reg_rmft2_ipv6_pack(rmft2_pl, true, parman_item->index,
					  key->vrid,
					  MLXSW_REG_RMFT2_IRIF_MASK_IGNORE, 0,
					  key->group.addr6,
					  key->group_mask.addr6,
					  key->source.addr6,
					  key->source_mask.addr6,
					  mlxsw_afa_block_first_set(afa_block));
	}

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(rmft2), rmft2_pl);
}