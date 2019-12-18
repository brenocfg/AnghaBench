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
struct rcar_du_wb_job {int /*<<< orphan*/  sg_tables; } ;
struct rcar_du_crtc {int /*<<< orphan*/  vsp; } ;
struct drm_writeback_job {int /*<<< orphan*/  fb; struct rcar_du_wb_job* priv; } ;
struct drm_writeback_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rcar_du_wb_job*) ; 
 int /*<<< orphan*/  rcar_du_vsp_unmap_fb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rcar_du_crtc* wb_to_rcar_crtc (struct drm_writeback_connector*) ; 

__attribute__((used)) static void rcar_du_wb_cleanup_job(struct drm_writeback_connector *connector,
				   struct drm_writeback_job *job)
{
	struct rcar_du_crtc *rcrtc = wb_to_rcar_crtc(connector);
	struct rcar_du_wb_job *rjob = job->priv;

	if (!job->fb)
		return;

	rcar_du_vsp_unmap_fb(rcrtc->vsp, job->fb, rjob->sg_tables);
	kfree(rjob);
}