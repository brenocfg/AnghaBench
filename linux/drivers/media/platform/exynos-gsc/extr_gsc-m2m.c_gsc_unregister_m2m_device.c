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
struct TYPE_2__ {int /*<<< orphan*/  m2m_dev; } ;
struct gsc_dev {int /*<<< orphan*/  vdev; TYPE_1__ m2m; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

void gsc_unregister_m2m_device(struct gsc_dev *gsc)
{
	if (gsc) {
		v4l2_m2m_release(gsc->m2m.m2m_dev);
		video_unregister_device(&gsc->vdev);
	}
}