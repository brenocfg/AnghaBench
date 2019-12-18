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
typedef  void* u8 ;
struct virtio_device {int dummy; } ;
struct virtio_ccw_device {int /*<<< orphan*/  cdev; TYPE_1__* dma_area; } ;
struct ccw1 {int count; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
typedef  int /*<<< orphan*/  status ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {void* status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_WRITE_STATUS ; 
 int /*<<< orphan*/  VIRTIO_CCW_DOING_WRITE_STATUS ; 
 int /*<<< orphan*/  ccw_device_dma_free (int /*<<< orphan*/ ,struct ccw1*,int) ; 
 struct ccw1* ccw_device_dma_zalloc (int /*<<< orphan*/ ,int) ; 
 int ccw_io_helper (struct virtio_ccw_device*,struct ccw1*,int /*<<< orphan*/ ) ; 
 struct virtio_ccw_device* to_vc_device (struct virtio_device*) ; 

__attribute__((used)) static void virtio_ccw_set_status(struct virtio_device *vdev, u8 status)
{
	struct virtio_ccw_device *vcdev = to_vc_device(vdev);
	u8 old_status = vcdev->dma_area->status;
	struct ccw1 *ccw;
	int ret;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		return;

	/* Write the status to the host. */
	vcdev->dma_area->status = status;
	ccw->cmd_code = CCW_CMD_WRITE_STATUS;
	ccw->flags = 0;
	ccw->count = sizeof(status);
	ccw->cda = (__u32)(unsigned long)&vcdev->dma_area->status;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_WRITE_STATUS);
	/* Write failed? We assume status is unchanged. */
	if (ret)
		vcdev->dma_area->status = old_status;
	ccw_device_dma_free(vcdev->cdev, ccw, sizeof(*ccw));
}