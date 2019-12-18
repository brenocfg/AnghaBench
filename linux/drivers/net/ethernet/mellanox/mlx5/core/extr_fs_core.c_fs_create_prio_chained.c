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
struct mlx5_flow_namespace {int dummy; } ;
struct fs_prio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_TYPE_PRIO_CHAINS ; 
 struct fs_prio* _fs_create_prio (struct mlx5_flow_namespace*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fs_prio *fs_create_prio_chained(struct mlx5_flow_namespace *ns,
					      unsigned int prio,
					      int num_levels)
{
	return _fs_create_prio(ns, prio, num_levels, FS_TYPE_PRIO_CHAINS);
}