#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_fib_entry {TYPE_3__* fib_node; } ;
struct mlxsw_sp_fib {int proto; TYPE_1__* vr; } ;
typedef  enum mlxsw_reg_ralxx_protocol { ____Placeholder_mlxsw_reg_ralxx_protocol } mlxsw_reg_ralxx_protocol ;
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;
struct TYPE_5__ {scalar_t__ addr; int /*<<< orphan*/  prefix_len; } ;
struct TYPE_6__ {TYPE_2__ key; struct mlxsw_sp_fib* fib; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 
 int /*<<< orphan*/  mlxsw_reg_ralue_pack4 (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_pack6 (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mlxsw_sp_fib_entry_ralue_pack(char *ralue_pl,
			      const struct mlxsw_sp_fib_entry *fib_entry,
			      enum mlxsw_reg_ralue_op op)
{
	struct mlxsw_sp_fib *fib = fib_entry->fib_node->fib;
	enum mlxsw_reg_ralxx_protocol proto;
	u32 *p_dip;

	proto = (enum mlxsw_reg_ralxx_protocol) fib->proto;

	switch (fib->proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		p_dip = (u32 *) fib_entry->fib_node->key.addr;
		mlxsw_reg_ralue_pack4(ralue_pl, proto, op, fib->vr->id,
				      fib_entry->fib_node->key.prefix_len,
				      *p_dip);
		break;
	case MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_reg_ralue_pack6(ralue_pl, proto, op, fib->vr->id,
				      fib_entry->fib_node->key.prefix_len,
				      fib_entry->fib_node->key.addr);
		break;
	}
}