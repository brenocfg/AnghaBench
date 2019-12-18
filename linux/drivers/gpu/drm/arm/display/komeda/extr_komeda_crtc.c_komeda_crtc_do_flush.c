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
struct TYPE_8__ {struct drm_connector_state* state; } ;
struct TYPE_10__ {TYPE_3__ base; } ;
struct komeda_wb_connector {TYPE_5__ base; } ;
struct komeda_pipeline {int /*<<< orphan*/  id; } ;
struct komeda_dev {TYPE_4__* funcs; } ;
struct komeda_crtc_state {int /*<<< orphan*/  active_pipes; int /*<<< orphan*/  affected_pipes; } ;
struct TYPE_7__ {TYPE_1__* dev; } ;
struct komeda_crtc {struct komeda_wb_connector* wb_conn; struct komeda_pipeline* slave; struct komeda_pipeline* master; TYPE_2__ base; } ;
struct drm_crtc_state {int /*<<< orphan*/  state; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;
struct drm_connector_state {scalar_t__ writeback_job; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* flush ) (struct komeda_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {struct komeda_dev* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_writeback_queue_job (TYPE_5__*,struct drm_connector_state*) ; 
 scalar_t__ has_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_pipeline_update (struct komeda_pipeline*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct komeda_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct komeda_crtc* to_kcrtc (struct drm_crtc*) ; 
 struct komeda_crtc_state* to_kcrtc_st (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
komeda_crtc_do_flush(struct drm_crtc *crtc,
		     struct drm_crtc_state *old)
{
	struct komeda_crtc *kcrtc = to_kcrtc(crtc);
	struct komeda_crtc_state *kcrtc_st = to_kcrtc_st(crtc->state);
	struct komeda_dev *mdev = kcrtc->base.dev->dev_private;
	struct komeda_pipeline *master = kcrtc->master;
	struct komeda_pipeline *slave = kcrtc->slave;
	struct komeda_wb_connector *wb_conn = kcrtc->wb_conn;
	struct drm_connector_state *conn_st;

	DRM_DEBUG_ATOMIC("CRTC%d_FLUSH: active_pipes: 0x%x, affected: 0x%x.\n",
			 drm_crtc_index(crtc),
			 kcrtc_st->active_pipes, kcrtc_st->affected_pipes);

	/* step 1: update the pipeline/component state to HW */
	if (has_bit(master->id, kcrtc_st->affected_pipes))
		komeda_pipeline_update(master, old->state);

	if (slave && has_bit(slave->id, kcrtc_st->affected_pipes))
		komeda_pipeline_update(slave, old->state);

	conn_st = wb_conn ? wb_conn->base.base.state : NULL;
	if (conn_st && conn_st->writeback_job)
		drm_writeback_queue_job(&wb_conn->base, conn_st);

	/* step 2: notify the HW to kickoff the update */
	mdev->funcs->flush(mdev, master->id, kcrtc_st->active_pipes);
}