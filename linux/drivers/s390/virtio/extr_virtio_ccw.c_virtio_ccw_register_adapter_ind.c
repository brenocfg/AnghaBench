#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtqueue {int dummy; } ;
struct virtio_thinint_area {unsigned long summary_indicator; int /*<<< orphan*/  isc; int /*<<< orphan*/  indicator; int /*<<< orphan*/  bit_nr; } ;
struct virtio_ccw_device {TYPE_1__* cdev; struct airq_info* airq_info; } ;
struct ccw1 {int count; scalar_t__ cda; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
struct airq_info {int dummy; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_SET_IND_ADAPTER ; 
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  VIRTIO_AIRQ_ISC ; 
 int /*<<< orphan*/  VIRTIO_CCW_DOING_SET_IND_ADAPTER ; 
 int /*<<< orphan*/  ccw_device_dma_free (TYPE_1__*,struct virtio_thinint_area*,int) ; 
 struct virtio_thinint_area* ccw_device_dma_zalloc (TYPE_1__*,int) ; 
 int ccw_io_helper (struct virtio_ccw_device*,struct ccw1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  get_airq_indicator (struct virtqueue**,int,int /*<<< orphan*/ *,struct airq_info**) ; 
 scalar_t__ get_summary_indicator (struct airq_info*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  virtio_ccw_drop_indicators (struct virtio_ccw_device*) ; 
 scalar_t__ virtio_ccw_use_airq ; 

__attribute__((used)) static int virtio_ccw_register_adapter_ind(struct virtio_ccw_device *vcdev,
					   struct virtqueue *vqs[], int nvqs,
					   struct ccw1 *ccw)
{
	int ret;
	struct virtio_thinint_area *thinint_area = NULL;
	struct airq_info *info;

	thinint_area = ccw_device_dma_zalloc(vcdev->cdev,
					     sizeof(*thinint_area));
	if (!thinint_area) {
		ret = -ENOMEM;
		goto out;
	}
	/* Try to get an indicator. */
	thinint_area->indicator = get_airq_indicator(vqs, nvqs,
						     &thinint_area->bit_nr,
						     &vcdev->airq_info);
	if (!thinint_area->indicator) {
		ret = -ENOSPC;
		goto out;
	}
	info = vcdev->airq_info;
	thinint_area->summary_indicator =
		(unsigned long) get_summary_indicator(info);
	thinint_area->isc = VIRTIO_AIRQ_ISC;
	ccw->cmd_code = CCW_CMD_SET_IND_ADAPTER;
	ccw->flags = CCW_FLAG_SLI;
	ccw->count = sizeof(*thinint_area);
	ccw->cda = (__u32)(unsigned long)thinint_area;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_SET_IND_ADAPTER);
	if (ret) {
		if (ret == -EOPNOTSUPP) {
			/*
			 * The host does not support adapter interrupts
			 * for virtio-ccw, stop trying.
			 */
			virtio_ccw_use_airq = 0;
			pr_info("Adapter interrupts unsupported on host\n");
		} else
			dev_warn(&vcdev->cdev->dev,
				 "enabling adapter interrupts = %d\n", ret);
		virtio_ccw_drop_indicators(vcdev);
	}
out:
	ccw_device_dma_free(vcdev->cdev, thinint_area, sizeof(*thinint_area));
	return ret;
}