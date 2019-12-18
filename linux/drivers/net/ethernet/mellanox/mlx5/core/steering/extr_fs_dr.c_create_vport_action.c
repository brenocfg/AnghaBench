#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5dr_domain {int dummy; } ;
struct mlx5dr_action {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  vhca_id; int /*<<< orphan*/  num; } ;
struct mlx5_flow_destination {TYPE_1__ vport; } ;
struct mlx5_flow_rule {struct mlx5_flow_destination dest_attr; } ;

/* Variables and functions */
 int MLX5_FLOW_DEST_VPORT_VHCA_ID ; 
 struct mlx5dr_action* mlx5dr_action_create_dest_vport (struct mlx5dr_domain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5dr_action *create_vport_action(struct mlx5dr_domain *domain,
						 struct mlx5_flow_rule *dst)
{
	struct mlx5_flow_destination *dest_attr = &dst->dest_attr;

	return mlx5dr_action_create_dest_vport(domain, dest_attr->vport.num,
					       dest_attr->vport.flags &
					       MLX5_FLOW_DEST_VPORT_VHCA_ID,
					       dest_attr->vport.vhca_id);
}