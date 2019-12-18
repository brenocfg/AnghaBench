#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  size; scalar_t__ log_buf; int /*<<< orphan*/  dma; } ;
struct mlx5_fw_tracer {TYPE_2__ buff; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_fw_tracer_destroy_log_buf(struct mlx5_fw_tracer *tracer)
{
	struct mlx5_core_dev *dev = tracer->dev;
	struct device *ddev = &dev->pdev->dev;

	if (!tracer->buff.log_buf)
		return;

	dma_unmap_single(ddev, tracer->buff.dma, tracer->buff.size, DMA_FROM_DEVICE);
	free_pages((unsigned long)tracer->buff.log_buf, get_order(tracer->buff.size));
}