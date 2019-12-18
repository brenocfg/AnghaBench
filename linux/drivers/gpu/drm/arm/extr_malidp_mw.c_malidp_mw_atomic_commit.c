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
struct malidp_mw_connector_state {int rgb2yuv_initialized; int /*<<< orphan*/ * rgb2yuv_coeffs; int /*<<< orphan*/  format; int /*<<< orphan*/  n_planes; int /*<<< orphan*/ * pitches; int /*<<< orphan*/ * addrs; } ;
struct malidp_hw_device {TYPE_3__* hw; } ;
struct TYPE_4__ {struct drm_connector_state* state; } ;
struct drm_writeback_connector {TYPE_1__ base; } ;
struct malidp_drm {struct malidp_hw_device* dev; struct drm_writeback_connector mw_connector; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_device {int /*<<< orphan*/  dev; struct malidp_drm* dev_private; } ;
struct drm_connector_state {TYPE_2__* writeback_job; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* disable_memwrite ) (struct malidp_hw_device*) ;int /*<<< orphan*/  (* enable_memwrite ) (struct malidp_hw_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  drm_writeback_queue_job (struct drm_writeback_connector*,struct drm_connector_state*) ; 
 int /*<<< orphan*/  stub1 (struct malidp_hw_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct malidp_hw_device*) ; 
 struct malidp_mw_connector_state* to_mw_state (struct drm_connector_state*) ; 

void malidp_mw_atomic_commit(struct drm_device *drm,
			     struct drm_atomic_state *old_state)
{
	struct malidp_drm *malidp = drm->dev_private;
	struct drm_writeback_connector *mw_conn = &malidp->mw_connector;
	struct drm_connector_state *conn_state = mw_conn->base.state;
	struct malidp_hw_device *hwdev = malidp->dev;
	struct malidp_mw_connector_state *mw_state;

	if (!conn_state)
		return;

	mw_state = to_mw_state(conn_state);

	if (conn_state->writeback_job) {
		struct drm_framebuffer *fb = conn_state->writeback_job->fb;

		DRM_DEV_DEBUG_DRIVER(drm->dev,
				     "Enable memwrite %ux%u:%d %pad fmt: %u\n",
				     fb->width, fb->height,
				     mw_state->pitches[0],
				     &mw_state->addrs[0],
				     mw_state->format);

		drm_writeback_queue_job(mw_conn, conn_state);
		hwdev->hw->enable_memwrite(hwdev, mw_state->addrs,
					   mw_state->pitches, mw_state->n_planes,
					   fb->width, fb->height, mw_state->format,
					   !mw_state->rgb2yuv_initialized ?
					   mw_state->rgb2yuv_coeffs : NULL);
		mw_state->rgb2yuv_initialized = !!mw_state->rgb2yuv_coeffs;
	} else {
		DRM_DEV_DEBUG_DRIVER(drm->dev, "Disable memwrite\n");
		hwdev->hw->disable_memwrite(hwdev);
	}
}