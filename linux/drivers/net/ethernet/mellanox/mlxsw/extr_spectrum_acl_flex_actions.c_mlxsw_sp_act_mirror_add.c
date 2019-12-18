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
struct net_device {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp {struct mlxsw_sp_port** ports; } ;
typedef  enum mlxsw_sp_span_type { ____Placeholder_mlxsw_sp_span_type } mlxsw_sp_span_type ;

/* Variables and functions */
 int MLXSW_SP_SPAN_EGRESS ; 
 int MLXSW_SP_SPAN_INGRESS ; 
 int mlxsw_sp_span_mirror_add (struct mlxsw_sp_port*,struct net_device const*,int,int,int*) ; 

__attribute__((used)) static int
mlxsw_sp_act_mirror_add(void *priv, u8 local_in_port,
			const struct net_device *out_dev,
			bool ingress, int *p_span_id)
{
	struct mlxsw_sp_port *in_port;
	struct mlxsw_sp *mlxsw_sp = priv;
	enum mlxsw_sp_span_type type;

	type = ingress ? MLXSW_SP_SPAN_INGRESS : MLXSW_SP_SPAN_EGRESS;
	in_port = mlxsw_sp->ports[local_in_port];

	return mlxsw_sp_span_mirror_add(in_port, out_dev, type,
					false, p_span_id);
}