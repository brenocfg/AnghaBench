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
struct mlx5_pkt_reformat {int ns_type; int reformat_type; } ;
struct mlx5_flow_root_namespace {TYPE_1__* cmds; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_flow_namespace_type { ____Placeholder_mlx5_flow_namespace_type } mlx5_flow_namespace_type ;
struct TYPE_2__ {int (* packet_reformat_alloc ) (struct mlx5_flow_root_namespace*,int,size_t,void*,int,struct mlx5_pkt_reformat*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct mlx5_pkt_reformat* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx5_flow_root_namespace* get_root_namespace (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  kfree (struct mlx5_pkt_reformat*) ; 
 struct mlx5_pkt_reformat* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlx5_flow_root_namespace*,int,size_t,void*,int,struct mlx5_pkt_reformat*) ; 

struct mlx5_pkt_reformat *mlx5_packet_reformat_alloc(struct mlx5_core_dev *dev,
						     int reformat_type,
						     size_t size,
						     void *reformat_data,
						     enum mlx5_flow_namespace_type ns_type)
{
	struct mlx5_pkt_reformat *pkt_reformat;
	struct mlx5_flow_root_namespace *root;
	int err;

	root = get_root_namespace(dev, ns_type);
	if (!root)
		return ERR_PTR(-EOPNOTSUPP);

	pkt_reformat = kzalloc(sizeof(*pkt_reformat), GFP_KERNEL);
	if (!pkt_reformat)
		return ERR_PTR(-ENOMEM);

	pkt_reformat->ns_type = ns_type;
	pkt_reformat->reformat_type = reformat_type;
	err = root->cmds->packet_reformat_alloc(root, reformat_type, size,
						reformat_data, ns_type,
						pkt_reformat);
	if (err) {
		kfree(pkt_reformat);
		return ERR_PTR(err);
	}

	return pkt_reformat;
}