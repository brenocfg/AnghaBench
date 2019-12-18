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
struct TYPE_5__ {int handle_in_r3; int /*<<< orphan*/  balloon_chunks; } ;
struct TYPE_6__ {TYPE_2__ out; } ;
struct vbg_ioctl_check_balloon {TYPE_3__ u; int /*<<< orphan*/  hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  chunks; } ;
struct vbg_dev {TYPE_1__ mem_balloon; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ vbg_ioctl_chk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vbg_ioctl_check_balloon(struct vbg_dev *gdev,
				   struct vbg_ioctl_check_balloon *balloon_info)
{
	if (vbg_ioctl_chk(&balloon_info->hdr, 0, sizeof(balloon_info->u.out)))
		return -EINVAL;

	balloon_info->u.out.balloon_chunks = gdev->mem_balloon.chunks;
	/*
	 * Under Linux we handle VMMDEV_EVENT_BALLOON_CHANGE_REQUEST
	 * events entirely in the kernel, see vbg_core_isr().
	 */
	balloon_info->u.out.handle_in_r3 = false;

	return 0;
}