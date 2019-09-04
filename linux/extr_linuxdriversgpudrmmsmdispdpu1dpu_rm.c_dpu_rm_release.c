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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {TYPE_1__ base; } ;
struct drm_connector {int dummy; } ;
struct dpu_rm_rsvp {int dummy; } ;
struct dpu_rm {int /*<<< orphan*/  rm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 struct drm_connector* _dpu_rm_get_connector (struct drm_encoder*) ; 
 struct dpu_rm_rsvp* _dpu_rm_get_rsvp (struct dpu_rm*,struct drm_encoder*) ; 
 int /*<<< orphan*/  _dpu_rm_release_rsvp (struct dpu_rm*,struct dpu_rm_rsvp*,struct drm_connector*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dpu_rm_release(struct dpu_rm *rm, struct drm_encoder *enc)
{
	struct dpu_rm_rsvp *rsvp;
	struct drm_connector *conn;

	if (!rm || !enc) {
		DPU_ERROR("invalid params\n");
		return;
	}

	mutex_lock(&rm->rm_lock);

	rsvp = _dpu_rm_get_rsvp(rm, enc);
	if (!rsvp) {
		DPU_ERROR("failed to find rsvp for enc %d\n", enc->base.id);
		goto end;
	}

	conn = _dpu_rm_get_connector(enc);
	if (!conn) {
		DPU_ERROR("failed to get connector for enc %d\n", enc->base.id);
		goto end;
	}

	_dpu_rm_release_rsvp(rm, rsvp, conn);
end:
	mutex_unlock(&rm->rm_lock);
}