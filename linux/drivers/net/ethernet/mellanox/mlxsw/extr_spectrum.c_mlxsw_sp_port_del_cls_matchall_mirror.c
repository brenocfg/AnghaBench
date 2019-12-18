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
struct mlxsw_sp_port_mall_mirror_tc_entry {int /*<<< orphan*/  span_id; scalar_t__ ingress; } ;
struct mlxsw_sp_port {int dummy; } ;
typedef  enum mlxsw_sp_span_type { ____Placeholder_mlxsw_sp_span_type } mlxsw_sp_span_type ;

/* Variables and functions */
 int MLXSW_SP_SPAN_EGRESS ; 
 int MLXSW_SP_SPAN_INGRESS ; 
 int /*<<< orphan*/  mlxsw_sp_span_mirror_del (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
mlxsw_sp_port_del_cls_matchall_mirror(struct mlxsw_sp_port *mlxsw_sp_port,
				      struct mlxsw_sp_port_mall_mirror_tc_entry *mirror)
{
	enum mlxsw_sp_span_type span_type;

	span_type = mirror->ingress ?
			MLXSW_SP_SPAN_INGRESS : MLXSW_SP_SPAN_EGRESS;
	mlxsw_sp_span_mirror_del(mlxsw_sp_port, mirror->span_id,
				 span_type, true);
}