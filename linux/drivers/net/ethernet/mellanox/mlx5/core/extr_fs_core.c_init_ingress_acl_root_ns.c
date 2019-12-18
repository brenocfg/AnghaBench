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
struct mlx5_flow_steering {TYPE_1__** esw_ingress_root_ns; } ;
struct fs_prio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FS_FT_ESW_INGRESS_ACL ; 
 int PTR_ERR_OR_ZERO (struct fs_prio*) ; 
 TYPE_1__* create_root_ns (struct mlx5_flow_steering*,int /*<<< orphan*/ ) ; 
 struct fs_prio* fs_create_prio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_ingress_acl_root_ns(struct mlx5_flow_steering *steering, int vport)
{
	struct fs_prio *prio;

	steering->esw_ingress_root_ns[vport] = create_root_ns(steering, FS_FT_ESW_INGRESS_ACL);
	if (!steering->esw_ingress_root_ns[vport])
		return -ENOMEM;

	/* create 1 prio*/
	prio = fs_create_prio(&steering->esw_ingress_root_ns[vport]->ns, 0, 1);
	return PTR_ERR_OR_ZERO(prio);
}