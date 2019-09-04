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
struct mlxsw_sp_port {int /*<<< orphan*/  dev; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 129 
#define  TC_SETUP_CLSMATCHALL 128 
 int mlxsw_sp_setup_tc_cls_matchall (struct mlxsw_sp_port*,void*,int) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int mlxsw_sp_setup_tc_block_cb_matchall(enum tc_setup_type type,
					       void *type_data,
					       void *cb_priv, bool ingress)
{
	struct mlxsw_sp_port *mlxsw_sp_port = cb_priv;

	switch (type) {
	case TC_SETUP_CLSMATCHALL:
		if (!tc_cls_can_offload_and_chain0(mlxsw_sp_port->dev,
						   type_data))
			return -EOPNOTSUPP;

		return mlxsw_sp_setup_tc_cls_matchall(mlxsw_sp_port, type_data,
						      ingress);
	case TC_SETUP_CLSFLOWER:
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}