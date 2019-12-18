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
struct dpu_crtc {int /*<<< orphan*/  vblank_cb_count; int /*<<< orphan*/  vblank_cb_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRMID (struct drm_crtc*) ; 
 int /*<<< orphan*/  _dpu_crtc_complete_flip (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (struct drm_crtc*) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  trace_dpu_crtc_vblank_cb (int /*<<< orphan*/ ) ; 

void dpu_crtc_vblank_callback(struct drm_crtc *crtc)
{
	struct dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);

	/* keep statistics on vblank callback - with auto reset via debugfs */
	if (ktime_compare(dpu_crtc->vblank_cb_time, ktime_set(0, 0)) == 0)
		dpu_crtc->vblank_cb_time = ktime_get();
	else
		dpu_crtc->vblank_cb_count++;
	_dpu_crtc_complete_flip(crtc);
	drm_crtc_handle_vblank(crtc);
	trace_dpu_crtc_vblank_cb(DRMID(crtc));
}