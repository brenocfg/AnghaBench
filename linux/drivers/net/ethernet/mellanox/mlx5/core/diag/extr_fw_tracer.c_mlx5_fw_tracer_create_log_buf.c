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
struct TYPE_4__ {int /*<<< orphan*/  size; void* log_buf; int /*<<< orphan*/  dma; } ;
struct mlx5_fw_tracer {TYPE_2__ buff; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  TRACE_BUFFER_SIZE_BYTE ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 

__attribute__((used)) static int mlx5_fw_tracer_create_log_buf(struct mlx5_fw_tracer *tracer)
{
	struct mlx5_core_dev *dev = tracer->dev;
	struct device *ddev = &dev->pdev->dev;
	dma_addr_t dma;
	void *buff;
	gfp_t gfp;
	int err;

	tracer->buff.size = TRACE_BUFFER_SIZE_BYTE;

	gfp = GFP_KERNEL | __GFP_ZERO;
	buff = (void *)__get_free_pages(gfp,
					get_order(tracer->buff.size));
	if (!buff) {
		err = -ENOMEM;
		mlx5_core_warn(dev, "FWTracer: Failed to allocate pages, %d\n", err);
		return err;
	}
	tracer->buff.log_buf = buff;

	dma = dma_map_single(ddev, buff, tracer->buff.size, DMA_FROM_DEVICE);
	if (dma_mapping_error(ddev, dma)) {
		mlx5_core_warn(dev, "FWTracer: Unable to map DMA: %d\n",
			       dma_mapping_error(ddev, dma));
		err = -ENOMEM;
		goto free_pages;
	}
	tracer->buff.dma = dma;

	return 0;

free_pages:
	free_pages((unsigned long)tracer->buff.log_buf, get_order(tracer->buff.size));

	return err;
}