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
struct drm_writeback_job {struct rcar_du_wb_job* priv; int /*<<< orphan*/  fb; } ;
struct drm_writeback_connector {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct rcar_du_wb_job*) ; 
 struct rcar_du_wb_job* kzalloc (int,int /*<<< orphan*/ ) ; 
 int rcar_du_vsp_map_fb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rcar_du_crtc* wb_to_rcar_crtc (struct drm_writeback_connector*) ; 

__attribute__((used)) static int rcar_du_wb_prepare_job(struct drm_writeback_connector *connector,
				  struct drm_writeback_job *job)
{
	struct rcar_du_crtc *rcrtc = wb_to_rcar_crtc(connector);
	struct rcar_du_wb_job *rjob;
	int ret;

	if (!job->fb)
		return 0;

	rjob = kzalloc(sizeof(*rjob), GFP_KERNEL);
	if (!rjob)
		return -ENOMEM;

	/* Map the framebuffer to the VSP. */
	ret = rcar_du_vsp_map_fb(rcrtc->vsp, job->fb, rjob->sg_tables);
	if (ret < 0) {
		kfree(rjob);
		return ret;
	}

	job->priv = rjob;
	return 0;
}