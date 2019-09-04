#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_flow_steering {TYPE_1__* fdb_root_ns; } ;
struct fs_prio {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FS_FT_FDB ; 
 scalar_t__ IS_ERR (struct fs_prio*) ; 
 int PTR_ERR (struct fs_prio*) ; 
 int /*<<< orphan*/  cleanup_root_ns (TYPE_1__*) ; 
 TYPE_1__* create_root_ns (struct mlx5_flow_steering*,int /*<<< orphan*/ ) ; 
 struct fs_prio* fs_create_prio (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  set_prio_attrs (TYPE_1__*) ; 

__attribute__((used)) static int init_fdb_root_ns(struct mlx5_flow_steering *steering)
{
	struct fs_prio *prio;

	steering->fdb_root_ns = create_root_ns(steering, FS_FT_FDB);
	if (!steering->fdb_root_ns)
		return -ENOMEM;

	prio = fs_create_prio(&steering->fdb_root_ns->ns, 0, 2);
	if (IS_ERR(prio))
		goto out_err;

	prio = fs_create_prio(&steering->fdb_root_ns->ns, 1, 1);
	if (IS_ERR(prio))
		goto out_err;

	set_prio_attrs(steering->fdb_root_ns);
	return 0;

out_err:
	cleanup_root_ns(steering->fdb_root_ns);
	steering->fdb_root_ns = NULL;
	return PTR_ERR(prio);
}