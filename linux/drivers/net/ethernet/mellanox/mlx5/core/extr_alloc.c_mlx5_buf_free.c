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
struct mlx5_frag_buf {TYPE_1__* frags; int /*<<< orphan*/  size; } ;
struct mlx5_core_dev {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void mlx5_buf_free(struct mlx5_core_dev *dev, struct mlx5_frag_buf *buf)
{
	dma_free_coherent(dev->device, buf->size, buf->frags->buf,
			  buf->frags->map);

	kfree(buf->frags);
}