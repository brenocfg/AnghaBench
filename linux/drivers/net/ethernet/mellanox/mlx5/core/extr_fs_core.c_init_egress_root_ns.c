#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx5_flow_steering {TYPE_2__* egress_root_ns; } ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
struct TYPE_6__ {TYPE_1__ ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FS_FT_NIC_TX ; 
 int /*<<< orphan*/  cleanup_root_ns (TYPE_2__*) ; 
 TYPE_2__* create_root_ns (struct mlx5_flow_steering*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egress_root_fs ; 
 int init_root_tree (struct mlx5_flow_steering*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_prio_attrs (TYPE_2__*) ; 

__attribute__((used)) static int init_egress_root_ns(struct mlx5_flow_steering *steering)
{
	int err;

	steering->egress_root_ns = create_root_ns(steering,
						  FS_FT_NIC_TX);
	if (!steering->egress_root_ns)
		return -ENOMEM;

	err = init_root_tree(steering, &egress_root_fs,
			     &steering->egress_root_ns->ns.node);
	if (err)
		goto cleanup;
	set_prio_attrs(steering->egress_root_ns);
	return 0;
cleanup:
	cleanup_root_ns(steering->egress_root_ns);
	steering->egress_root_ns = NULL;
	return err;
}