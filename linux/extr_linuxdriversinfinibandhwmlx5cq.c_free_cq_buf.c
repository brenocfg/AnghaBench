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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  frag_buf; } ;
struct mlx5_ib_cq_buf {TYPE_1__ fbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_frag_buf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_cq_buf(struct mlx5_ib_dev *dev, struct mlx5_ib_cq_buf *buf)
{
	mlx5_frag_buf_free(dev->mdev, &buf->fbc.frag_buf);
}