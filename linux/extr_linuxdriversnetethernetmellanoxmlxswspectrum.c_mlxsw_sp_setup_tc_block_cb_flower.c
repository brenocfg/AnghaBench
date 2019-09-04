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
struct mlxsw_sp_acl_block {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 129 
#define  TC_SETUP_CLSMATCHALL 128 
 int /*<<< orphan*/  mlxsw_sp_acl_block_disabled (struct mlxsw_sp_acl_block*) ; 
 int mlxsw_sp_setup_tc_cls_flower (struct mlxsw_sp_acl_block*,void*) ; 

__attribute__((used)) static int mlxsw_sp_setup_tc_block_cb_flower(enum tc_setup_type type,
					     void *type_data, void *cb_priv)
{
	struct mlxsw_sp_acl_block *acl_block = cb_priv;

	switch (type) {
	case TC_SETUP_CLSMATCHALL:
		return 0;
	case TC_SETUP_CLSFLOWER:
		if (mlxsw_sp_acl_block_disabled(acl_block))
			return -EOPNOTSUPP;

		return mlxsw_sp_setup_tc_cls_flower(acl_block, type_data);
	default:
		return -EOPNOTSUPP;
	}
}