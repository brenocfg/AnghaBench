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
struct TYPE_6__ {TYPE_2__* qfbdev; } ;
struct qxl_device {TYPE_3__ mode_info; } ;
struct qxl_bo {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
struct TYPE_5__ {TYPE_1__ qfb; } ;

/* Variables and functions */
 struct qxl_bo* gem_to_qxl_bo (int /*<<< orphan*/ ) ; 

bool qxl_fbdev_qobj_is_fb(struct qxl_device *qdev, struct qxl_bo *qobj)
{
	if (qobj == gem_to_qxl_bo(qdev->mode_info.qfbdev->qfb.obj))
		return true;
	return false;
}