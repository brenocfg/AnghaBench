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
typedef  size_t u8 ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp {struct mlxsw_sp_port** ports; } ;
typedef  enum mlxsw_sp_span_type { ____Placeholder_mlxsw_sp_span_type } mlxsw_sp_span_type ;

/* Variables and functions */
 int MLXSW_SP_SPAN_EGRESS ; 
 int MLXSW_SP_SPAN_INGRESS ; 
 int /*<<< orphan*/  mlxsw_sp_span_mirror_del (struct mlxsw_sp_port*,int,int,int) ; 

__attribute__((used)) static void
mlxsw_sp_act_mirror_del(void *priv, u8 local_in_port, int span_id, bool ingress)
{
	struct mlxsw_sp *mlxsw_sp = priv;
	struct mlxsw_sp_port *in_port;
	enum mlxsw_sp_span_type type;

	type = ingress ? MLXSW_SP_SPAN_INGRESS : MLXSW_SP_SPAN_EGRESS;
	in_port = mlxsw_sp->ports[local_in_port];

	mlxsw_sp_span_mirror_del(in_port, span_id, type, false);
}