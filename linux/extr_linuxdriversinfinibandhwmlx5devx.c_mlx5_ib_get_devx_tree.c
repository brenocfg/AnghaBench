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
struct uverbs_object_tree_def {int dummy; } ;

/* Variables and functions */
 struct uverbs_object_tree_def const devx_objects ; 

const struct uverbs_object_tree_def *mlx5_ib_get_devx_tree(void)
{
	return &devx_objects;
}