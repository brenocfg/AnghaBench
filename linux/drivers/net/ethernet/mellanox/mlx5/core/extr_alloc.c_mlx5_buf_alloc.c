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
struct mlx5_frag_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  numa_node; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int mlx5_buf_alloc_node (struct mlx5_core_dev*,int,struct mlx5_frag_buf*,int /*<<< orphan*/ ) ; 

int mlx5_buf_alloc(struct mlx5_core_dev *dev,
		   int size, struct mlx5_frag_buf *buf)
{
	return mlx5_buf_alloc_node(dev, size, buf, dev->priv.numa_node);
}