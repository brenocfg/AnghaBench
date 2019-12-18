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
struct mlx5_pkt_reformat {int /*<<< orphan*/  ns_type; } ;
struct mlx5_flow_root_namespace {TYPE_1__* cmds; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* packet_reformat_dealloc ) (struct mlx5_flow_root_namespace*,struct mlx5_pkt_reformat*) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct mlx5_flow_root_namespace* get_root_namespace (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_pkt_reformat*) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_flow_root_namespace*,struct mlx5_pkt_reformat*) ; 

void mlx5_packet_reformat_dealloc(struct mlx5_core_dev *dev,
				  struct mlx5_pkt_reformat *pkt_reformat)
{
	struct mlx5_flow_root_namespace *root;

	root = get_root_namespace(dev, pkt_reformat->ns_type);
	if (WARN_ON(!root))
		return;
	root->cmds->packet_reformat_dealloc(root, pkt_reformat);
	kfree(pkt_reformat);
}