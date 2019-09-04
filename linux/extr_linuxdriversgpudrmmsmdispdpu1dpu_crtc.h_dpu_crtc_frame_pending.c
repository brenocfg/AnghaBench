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
struct drm_crtc {int dummy; } ;
struct dpu_crtc {int /*<<< orphan*/  frame_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static inline int dpu_crtc_frame_pending(struct drm_crtc *crtc)
{
	struct dpu_crtc *dpu_crtc;

	if (!crtc)
		return -EINVAL;

	dpu_crtc = to_dpu_crtc(crtc);
	return atomic_read(&dpu_crtc->frame_pending);
}