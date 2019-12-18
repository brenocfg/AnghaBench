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
struct tc_cls_matchall_offload {int command; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSMATCHALL_DESTROY 129 
#define  TC_CLSMATCHALL_REPLACE 128 
 int mlxsw_sp_port_add_cls_matchall (struct mlxsw_sp_port*,struct tc_cls_matchall_offload*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_del_cls_matchall (struct mlxsw_sp_port*,struct tc_cls_matchall_offload*) ; 

__attribute__((used)) static int mlxsw_sp_setup_tc_cls_matchall(struct mlxsw_sp_port *mlxsw_sp_port,
					  struct tc_cls_matchall_offload *f,
					  bool ingress)
{
	switch (f->command) {
	case TC_CLSMATCHALL_REPLACE:
		return mlxsw_sp_port_add_cls_matchall(mlxsw_sp_port, f,
						      ingress);
	case TC_CLSMATCHALL_DESTROY:
		mlxsw_sp_port_del_cls_matchall(mlxsw_sp_port, f);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}