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
struct qxl_head {int id; scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; scalar_t__ flags; } ;
struct qxl_device {scalar_t__ primary_bo; scalar_t__ dumb_shadow_bo; TYPE_3__* monitors_config; TYPE_1__* dumb_heads; } ;
struct qxl_crtc {int index; } ;
struct drm_display_mode {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_device {struct qxl_device* dev_private; } ;
struct drm_crtc {scalar_t__ x; scalar_t__ y; TYPE_2__* state; struct drm_display_mode mode; struct drm_device* dev; } ;
struct TYPE_6__ {int count; int max_allowed; struct qxl_head* heads; } ;
struct TYPE_5__ {scalar_t__ active; } ;
struct TYPE_4__ {scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int qxl_num_crtc ; 
 int /*<<< orphan*/  qxl_send_monitors_config (struct qxl_device*) ; 
 struct qxl_crtc* to_qxl_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void qxl_crtc_update_monitors_config(struct drm_crtc *crtc,
					    const char *reason)
{
	struct drm_device *dev = crtc->dev;
	struct qxl_device *qdev = dev->dev_private;
	struct qxl_crtc *qcrtc = to_qxl_crtc(crtc);
	struct qxl_head head;
	int oldcount, i = qcrtc->index;

	if (!qdev->primary_bo) {
		DRM_DEBUG_KMS("no primary surface, skip (%s)\n", reason);
		return;
	}

	if (!qdev->monitors_config || qxl_num_crtc <= i)
		return;

	head.id = i;
	head.flags = 0;
	oldcount = qdev->monitors_config->count;
	if (crtc->state->active) {
		struct drm_display_mode *mode = &crtc->mode;

		head.width = mode->hdisplay;
		head.height = mode->vdisplay;
		head.x = crtc->x;
		head.y = crtc->y;
		if (qdev->monitors_config->count < i + 1)
			qdev->monitors_config->count = i + 1;
		if (qdev->primary_bo == qdev->dumb_shadow_bo)
			head.x += qdev->dumb_heads[i].x;
	} else if (i > 0) {
		head.width = 0;
		head.height = 0;
		head.x = 0;
		head.y = 0;
		if (qdev->monitors_config->count == i + 1)
			qdev->monitors_config->count = i;
	} else {
		DRM_DEBUG_KMS("inactive head 0, skip (%s)\n", reason);
		return;
	}

	if (head.width  == qdev->monitors_config->heads[i].width  &&
	    head.height == qdev->monitors_config->heads[i].height &&
	    head.x      == qdev->monitors_config->heads[i].x      &&
	    head.y      == qdev->monitors_config->heads[i].y      &&
	    oldcount    == qdev->monitors_config->count)
		return;

	DRM_DEBUG_KMS("head %d, %dx%d, at +%d+%d, %s (%s)\n",
		      i, head.width, head.height, head.x, head.y,
		      crtc->state->active ? "on" : "off", reason);
	if (oldcount != qdev->monitors_config->count)
		DRM_DEBUG_KMS("active heads %d -> %d (%d total)\n",
			      oldcount, qdev->monitors_config->count,
			      qxl_num_crtc);

	qdev->monitors_config->heads[i] = head;
	qdev->monitors_config->max_allowed = qxl_num_crtc;
	qxl_send_monitors_config(qdev);
}