#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct TYPE_4__ {TYPE_2__ vfd; scalar_t__ m2m_dev; } ;
struct fimc_dev {TYPE_1__ m2m; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (scalar_t__) ; 
 scalar_t__ video_is_registered (TYPE_2__*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_2__*) ; 

void fimc_unregister_m2m_device(struct fimc_dev *fimc)
{
	if (!fimc)
		return;

	if (fimc->m2m.m2m_dev)
		v4l2_m2m_release(fimc->m2m.m2m_dev);

	if (video_is_registered(&fimc->m2m.vfd)) {
		video_unregister_device(&fimc->m2m.vfd);
		media_entity_cleanup(&fimc->m2m.vfd.entity);
	}
}