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
typedef  int /*<<< orphan*/  u8 ;
struct virtio_device {int dummy; } ;
struct virtio_ccw_device {int revision; TYPE_1__* dma_area; int /*<<< orphan*/  cdev; } ;
struct ccw1 {int count; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_READ_STATUS ; 
 int /*<<< orphan*/  VIRTIO_CCW_DOING_READ_STATUS ; 
 int /*<<< orphan*/  ccw_device_dma_free (int /*<<< orphan*/ ,struct ccw1*,int) ; 
 struct ccw1* ccw_device_dma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ccw_io_helper (struct virtio_ccw_device*,struct ccw1*,int /*<<< orphan*/ ) ; 
 struct virtio_ccw_device* to_vc_device (struct virtio_device*) ; 

__attribute__((used)) static u8 virtio_ccw_get_status(struct virtio_device *vdev)
{
	struct virtio_ccw_device *vcdev = to_vc_device(vdev);
	u8 old_status = vcdev->dma_area->status;
	struct ccw1 *ccw;

	if (vcdev->revision < 1)
		return vcdev->dma_area->status;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		return old_status;

	ccw->cmd_code = CCW_CMD_READ_STATUS;
	ccw->flags = 0;
	ccw->count = sizeof(vcdev->dma_area->status);
	ccw->cda = (__u32)(unsigned long)&vcdev->dma_area->status;
	ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_READ_STATUS);
/*
 * If the channel program failed (should only happen if the device
 * was hotunplugged, and then we clean up via the machine check
 * handler anyway), vcdev->dma_area->status was not overwritten and we just
 * return the old status, which is fine.
*/
	ccw_device_dma_free(vcdev->cdev, ccw, sizeof(*ccw));

	return vcdev->dma_area->status;
}