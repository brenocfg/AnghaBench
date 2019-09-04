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
struct mlx5_rsc_debug {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_rsc_debug*) ; 

__attribute__((used)) static void rem_res_tree(struct mlx5_rsc_debug *d)
{
	debugfs_remove_recursive(d->root);
	kfree(d);
}