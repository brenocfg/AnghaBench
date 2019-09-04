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
struct TYPE_2__ {scalar_t__ intr_type; } ;
struct vxgedev {int no_of_vpath; int /*<<< orphan*/  vp_reset_timer; int /*<<< orphan*/  devh; TYPE_1__ config; int /*<<< orphan*/  vp_reset; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ MSI_X ; 
 struct vxgedev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 
 struct vxgedev* vdev ; 
 int /*<<< orphan*/  vp_reset_timer ; 
 int /*<<< orphan*/  vxge_hw_device_flush_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_hw_device_unmask_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_reset_vpath (struct vxgedev*,int) ; 

__attribute__((used)) static void vxge_poll_vp_reset(struct timer_list *t)
{
	struct vxgedev *vdev = from_timer(vdev, t, vp_reset_timer);
	int i, j = 0;

	for (i = 0; i < vdev->no_of_vpath; i++) {
		if (test_bit(i, &vdev->vp_reset)) {
			vxge_reset_vpath(vdev, i);
			j++;
		}
	}
	if (j && (vdev->config.intr_type != MSI_X)) {
		vxge_hw_device_unmask_all(vdev->devh);
		vxge_hw_device_flush_io(vdev->devh);
	}

	mod_timer(&vdev->vp_reset_timer, jiffies + HZ / 2);
}