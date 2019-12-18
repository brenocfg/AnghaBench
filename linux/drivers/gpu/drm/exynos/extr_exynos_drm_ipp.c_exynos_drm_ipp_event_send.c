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
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct exynos_drm_ipp_task {TYPE_3__* event; TYPE_1__* ipp; } ;
struct TYPE_5__ {int tv_usec; int /*<<< orphan*/  sequence; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; TYPE_2__ event; } ;
struct TYPE_4__ {int /*<<< orphan*/  drm_dev; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 

__attribute__((used)) static void exynos_drm_ipp_event_send(struct exynos_drm_ipp_task *task)
{
	struct timespec64 now;

	ktime_get_ts64(&now);
	task->event->event.tv_sec = now.tv_sec;
	task->event->event.tv_usec = now.tv_nsec / NSEC_PER_USEC;
	task->event->event.sequence = atomic_inc_return(&task->ipp->sequence);

	drm_send_event(task->ipp->drm_dev, &task->event->base);
}