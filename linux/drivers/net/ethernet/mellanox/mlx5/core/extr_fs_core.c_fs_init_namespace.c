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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct mlx5_flow_namespace {TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_TYPE_NAMESPACE ; 

__attribute__((used)) static struct mlx5_flow_namespace *fs_init_namespace(struct mlx5_flow_namespace
						     *ns)
{
	ns->node.type = FS_TYPE_NAMESPACE;

	return ns;
}