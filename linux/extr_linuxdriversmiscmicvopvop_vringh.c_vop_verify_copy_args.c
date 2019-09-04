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
struct vop_vdev {TYPE_1__* dd; } ;
struct mic_copy_desc {scalar_t__ vr_idx; } ;
struct TYPE_2__ {scalar_t__ num_vq; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int vop_verify_copy_args(struct vop_vdev *vdev,
				       struct mic_copy_desc *copy)
{
	if (!vdev || copy->vr_idx >= vdev->dd->num_vq)
		return -EINVAL;
	return 0;
}