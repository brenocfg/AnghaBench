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
struct vq_config_block {int dummy; } ;
struct virtio_ccw_device {TYPE_2__* dma_area; } ;
struct ccw1 {int count; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_3__ {int index; scalar_t__ num; } ;
struct TYPE_4__ {TYPE_1__ config_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_READ_VQ_CONF ; 
 int ENOENT ; 
 int /*<<< orphan*/  VIRTIO_CCW_DOING_READ_VQ_CONF ; 
 int ccw_io_helper (struct virtio_ccw_device*,struct ccw1*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtio_ccw_read_vq_conf(struct virtio_ccw_device *vcdev,
				   struct ccw1 *ccw, int index)
{
	int ret;

	vcdev->dma_area->config_block.index = index;
	ccw->cmd_code = CCW_CMD_READ_VQ_CONF;
	ccw->flags = 0;
	ccw->count = sizeof(struct vq_config_block);
	ccw->cda = (__u32)(unsigned long)(&vcdev->dma_area->config_block);
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_READ_VQ_CONF);
	if (ret)
		return ret;
	return vcdev->dma_area->config_block.num ?: -ENOENT;
}