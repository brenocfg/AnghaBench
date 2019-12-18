#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iser_data_buf {int /*<<< orphan*/  dma_nents; int /*<<< orphan*/  size; int /*<<< orphan*/  sg; } ;
struct iscsi_iser_task {int* dir; TYPE_3__* iser_conn; } ;
struct ib_device {int dummy; } ;
typedef  enum iser_data_dir { ____Placeholder_iser_data_dir } iser_data_dir ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__ ib_conn; } ;
struct TYPE_4__ {struct ib_device* ib_device; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ib_dma_map_sg (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iser_err (char*) ; 

int iser_dma_map_task_data(struct iscsi_iser_task *iser_task,
			    struct iser_data_buf *data,
			    enum iser_data_dir iser_dir,
			    enum dma_data_direction dma_dir)
{
	struct ib_device *dev;

	iser_task->dir[iser_dir] = 1;
	dev = iser_task->iser_conn->ib_conn.device->ib_device;

	data->dma_nents = ib_dma_map_sg(dev, data->sg, data->size, dma_dir);
	if (data->dma_nents == 0) {
		iser_err("dma_map_sg failed!!!\n");
		return -EINVAL;
	}
	return 0;
}