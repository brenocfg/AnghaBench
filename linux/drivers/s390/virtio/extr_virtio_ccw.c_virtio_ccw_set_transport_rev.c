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
struct virtio_rev_info {int count; scalar_t__ revision; scalar_t__ length; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
struct virtio_ccw_device {scalar_t__ revision; int /*<<< orphan*/  cdev; } ;
struct ccw1 {int count; scalar_t__ revision; scalar_t__ length; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_SET_VIRTIO_REV ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  VIRTIO_CCW_DOING_SET_VIRTIO_REV ; 
 scalar_t__ VIRTIO_CCW_REV_MAX ; 
 int /*<<< orphan*/  ccw_device_dma_free (int /*<<< orphan*/ ,struct virtio_rev_info*,int) ; 
 struct virtio_rev_info* ccw_device_dma_zalloc (int /*<<< orphan*/ ,int) ; 
 int ccw_io_helper (struct virtio_ccw_device*,struct virtio_rev_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtio_ccw_set_transport_rev(struct virtio_ccw_device *vcdev)
{
	struct virtio_rev_info *rev;
	struct ccw1 *ccw;
	int ret;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, sizeof(*ccw));
	if (!ccw)
		return -ENOMEM;
	rev = ccw_device_dma_zalloc(vcdev->cdev, sizeof(*rev));
	if (!rev) {
		ccw_device_dma_free(vcdev->cdev, ccw, sizeof(*ccw));
		return -ENOMEM;
	}

	/* Set transport revision */
	ccw->cmd_code = CCW_CMD_SET_VIRTIO_REV;
	ccw->flags = 0;
	ccw->count = sizeof(*rev);
	ccw->cda = (__u32)(unsigned long)rev;

	vcdev->revision = VIRTIO_CCW_REV_MAX;
	do {
		rev->revision = vcdev->revision;
		/* none of our supported revisions carry payload */
		rev->length = 0;
		ret = ccw_io_helper(vcdev, ccw,
				    VIRTIO_CCW_DOING_SET_VIRTIO_REV);
		if (ret == -EOPNOTSUPP) {
			if (vcdev->revision == 0)
				/*
				 * The host device does not support setting
				 * the revision: let's operate it in legacy
				 * mode.
				 */
				ret = 0;
			else
				vcdev->revision--;
		}
	} while (ret == -EOPNOTSUPP);

	ccw_device_dma_free(vcdev->cdev, ccw, sizeof(*ccw));
	ccw_device_dma_free(vcdev->cdev, rev, sizeof(*rev));
	return ret;
}