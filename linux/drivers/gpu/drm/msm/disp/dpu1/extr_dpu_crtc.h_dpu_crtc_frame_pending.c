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
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  frame_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_dpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static inline int dpu_crtc_frame_pending(struct drm_crtc *crtc)
{
	return crtc ? atomic_read(&to_dpu_crtc(crtc)->frame_pending) : -EINVAL;
}