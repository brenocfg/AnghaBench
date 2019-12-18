#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {int /*<<< orphan*/  file_priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  time_ns; void* sequence; } ;
struct TYPE_7__ {int tv_usec; int /*<<< orphan*/  tv_sec; void* sequence; } ;
struct TYPE_6__ {int type; } ;
struct TYPE_9__ {TYPE_3__ seq; TYPE_2__ vbl; TYPE_1__ base; } ;
struct drm_pending_vblank_event {TYPE_5__ base; int /*<<< orphan*/  pipe; TYPE_4__ event; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
#define  DRM_EVENT_CRTC_SEQUENCE 130 
#define  DRM_EVENT_FLIP_COMPLETE 129 
#define  DRM_EVENT_VBLANK 128 
 int /*<<< orphan*/  drm_send_event_locked (struct drm_device*,TYPE_5__*) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_drm_vblank_event_delivered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void send_vblank_event(struct drm_device *dev,
		struct drm_pending_vblank_event *e,
		u64 seq, ktime_t now)
{
	struct timespec64 tv;

	switch (e->event.base.type) {
	case DRM_EVENT_VBLANK:
	case DRM_EVENT_FLIP_COMPLETE:
		tv = ktime_to_timespec64(now);
		e->event.vbl.sequence = seq;
		/*
		 * e->event is a user space structure, with hardcoded unsigned
		 * 32-bit seconds/microseconds. This is safe as we always use
		 * monotonic timestamps since linux-4.15
		 */
		e->event.vbl.tv_sec = tv.tv_sec;
		e->event.vbl.tv_usec = tv.tv_nsec / 1000;
		break;
	case DRM_EVENT_CRTC_SEQUENCE:
		if (seq)
			e->event.seq.sequence = seq;
		e->event.seq.time_ns = ktime_to_ns(now);
		break;
	}
	trace_drm_vblank_event_delivered(e->base.file_priv, e->pipe, seq);
	drm_send_event_locked(dev, &e->base);
}