#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct komeda_pipeline_state {scalar_t__ active_comps; } ;
struct komeda_pipeline {int /*<<< orphan*/  id; } ;
struct komeda_dev {TYPE_2__* funcs; } ;
struct komeda_crtc_state {int /*<<< orphan*/  active_pipes; int /*<<< orphan*/  affected_pipes; } ;
struct komeda_crtc {struct completion* disable_done; struct komeda_pipeline* master; struct komeda_pipeline* slave; } ;
struct drm_crtc_state {int /*<<< orphan*/  state; } ;
struct drm_crtc {TYPE_4__* dev; TYPE_3__* state; } ;
struct completion {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  event_lock; struct komeda_dev* dev_private; } ;
struct TYPE_7__ {scalar_t__ active; TYPE_1__* commit; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* flush ) (struct komeda_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {struct completion flip_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 scalar_t__ has_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  komeda_crtc_unprepare (struct komeda_crtc*) ; 
 int /*<<< orphan*/  komeda_pipeline_disable (struct komeda_pipeline*,int /*<<< orphan*/ ) ; 
 struct komeda_pipeline_state* komeda_pipeline_get_old_state (struct komeda_pipeline*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct komeda_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct komeda_crtc* to_kcrtc (struct drm_crtc*) ; 
 struct komeda_crtc_state* to_kcrtc_st (struct drm_crtc_state*) ; 
 int wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
komeda_crtc_atomic_disable(struct drm_crtc *crtc,
			   struct drm_crtc_state *old)
{
	struct komeda_crtc *kcrtc = to_kcrtc(crtc);
	struct komeda_crtc_state *old_st = to_kcrtc_st(old);
	struct komeda_dev *mdev = crtc->dev->dev_private;
	struct komeda_pipeline *master = kcrtc->master;
	struct komeda_pipeline *slave  = kcrtc->slave;
	struct completion *disable_done = &crtc->state->commit->flip_done;
	struct completion temp;
	int timeout;

	DRM_DEBUG_ATOMIC("CRTC%d_DISABLE: active_pipes: 0x%x, affected: 0x%x.\n",
			 drm_crtc_index(crtc),
			 old_st->active_pipes, old_st->affected_pipes);

	if (slave && has_bit(slave->id, old_st->active_pipes))
		komeda_pipeline_disable(slave, old->state);

	if (has_bit(master->id, old_st->active_pipes))
		komeda_pipeline_disable(master, old->state);

	/* crtc_disable has two scenarios according to the state->active switch.
	 * 1. active -> inactive
	 *    this commit is a disable commit. and the commit will be finished
	 *    or done after the disable operation. on this case we can directly
	 *    use the crtc->state->event to tracking the HW disable operation.
	 * 2. active -> active
	 *    the crtc->commit is not for disable, but a modeset operation when
	 *    crtc is active, such commit actually has been completed by 3
	 *    DRM operations:
	 *    crtc_disable, update_planes(crtc_flush), crtc_enable
	 *    so on this case the crtc->commit is for the whole process.
	 *    we can not use it for tracing the disable, we need a temporary
	 *    flip_done for tracing the disable. and crtc->state->event for
	 *    the crtc_enable operation.
	 *    That's also the reason why skip modeset commit in
	 *    komeda_crtc_atomic_flush()
	 */
	if (crtc->state->active) {
		struct komeda_pipeline_state *pipe_st;
		/* clear the old active_comps to zero */
		pipe_st = komeda_pipeline_get_old_state(master, old->state);
		pipe_st->active_comps = 0;

		init_completion(&temp);
		kcrtc->disable_done = &temp;
		disable_done = &temp;
	}

	mdev->funcs->flush(mdev, master->id, 0);

	/* wait the disable take affect.*/
	timeout = wait_for_completion_timeout(disable_done, HZ);
	if (timeout == 0) {
		DRM_ERROR("disable pipeline%d timeout.\n", kcrtc->master->id);
		if (crtc->state->active) {
			unsigned long flags;

			spin_lock_irqsave(&crtc->dev->event_lock, flags);
			kcrtc->disable_done = NULL;
			spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
		}
	}

	drm_crtc_vblank_off(crtc);
	komeda_crtc_unprepare(kcrtc);
}