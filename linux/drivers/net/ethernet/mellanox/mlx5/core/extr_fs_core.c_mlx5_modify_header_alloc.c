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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_modify_hdr {int /*<<< orphan*/  ns_type; } ;
struct mlx5_flow_root_namespace {TYPE_1__* cmds; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int (* modify_header_alloc ) (struct mlx5_flow_root_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct mlx5_modify_hdr*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct mlx5_modify_hdr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx5_flow_root_namespace* get_root_namespace (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_modify_hdr*) ; 
 struct mlx5_modify_hdr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlx5_flow_root_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct mlx5_modify_hdr*) ; 

struct mlx5_modify_hdr *mlx5_modify_header_alloc(struct mlx5_core_dev *dev,
						 u8 ns_type, u8 num_actions,
						 void *modify_actions)
{
	struct mlx5_flow_root_namespace *root;
	struct mlx5_modify_hdr *modify_hdr;
	int err;

	root = get_root_namespace(dev, ns_type);
	if (!root)
		return ERR_PTR(-EOPNOTSUPP);

	modify_hdr = kzalloc(sizeof(*modify_hdr), GFP_KERNEL);
	if (!modify_hdr)
		return ERR_PTR(-ENOMEM);

	modify_hdr->ns_type = ns_type;
	err = root->cmds->modify_header_alloc(root, ns_type, num_actions,
					      modify_actions, modify_hdr);
	if (err) {
		kfree(modify_hdr);
		return ERR_PTR(err);
	}

	return modify_hdr;
}