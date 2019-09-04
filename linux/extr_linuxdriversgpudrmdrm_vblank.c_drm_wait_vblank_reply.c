#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct timespec64 {int tv_nsec; scalar_t__ tv_sec; } ;
struct drm_wait_vblank_reply {int tval_usec; scalar_t__ tval_sec; int /*<<< orphan*/  sequence; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  drm_vblank_count_and_time (struct drm_device*,unsigned int,int /*<<< orphan*/ *) ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drm_wait_vblank_reply(struct drm_device *dev, unsigned int pipe,
				  struct drm_wait_vblank_reply *reply)
{
	ktime_t now;
	struct timespec64 ts;

	/*
	 * drm_wait_vblank_reply is a UAPI structure that uses 'long'
	 * to store the seconds. This is safe as we always use monotonic
	 * timestamps since linux-4.15.
	 */
	reply->sequence = drm_vblank_count_and_time(dev, pipe, &now);
	ts = ktime_to_timespec64(now);
	reply->tval_sec = (u32)ts.tv_sec;
	reply->tval_usec = ts.tv_nsec / 1000;
}