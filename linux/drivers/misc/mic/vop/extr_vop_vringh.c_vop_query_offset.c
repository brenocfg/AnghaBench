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
struct TYPE_6__ {unsigned long len; int /*<<< orphan*/  va; } ;
struct vop_vringh {TYPE_3__ vring; } ;
struct vop_vdev {struct vop_vringh* vvr; TYPE_2__* dd; struct vop_device* vpdev; } ;
struct vop_device {TYPE_1__* hw_ops; } ;
struct TYPE_5__ {int num_vq; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_dp ) (struct vop_device*) ;} ;

/* Variables and functions */
 unsigned long MIC_DP_SIZE ; 
 int /*<<< orphan*/  stub1 (struct vop_device*) ; 
 unsigned long virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
vop_query_offset(struct vop_vdev *vdev, unsigned long offset,
		 unsigned long *size, unsigned long *pa)
{
	struct vop_device *vpdev = vdev->vpdev;
	unsigned long start = MIC_DP_SIZE;
	int i;

	/*
	 * MMAP interface is as follows:
	 * offset				region
	 * 0x0					virtio device_page
	 * 0x1000				first vring
	 * 0x1000 + size of 1st vring		second vring
	 * ....
	 */
	if (!offset) {
		*pa = virt_to_phys(vpdev->hw_ops->get_dp(vpdev));
		*size = MIC_DP_SIZE;
		return 0;
	}

	for (i = 0; i < vdev->dd->num_vq; i++) {
		struct vop_vringh *vvr = &vdev->vvr[i];

		if (offset == start) {
			*pa = virt_to_phys(vvr->vring.va);
			*size = vvr->vring.len;
			return 0;
		}
		start += vvr->vring.len;
	}
	return -1;
}