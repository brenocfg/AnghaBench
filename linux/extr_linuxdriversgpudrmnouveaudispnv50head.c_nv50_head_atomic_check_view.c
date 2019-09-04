#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_14__ {int view; } ;
struct TYPE_13__ {int iW; int iH; int oW; int oH; } ;
struct drm_display_mode {int vdisplay; int flags; int hdisplay; scalar_t__ vtotal; } ;
struct TYPE_9__ {struct drm_display_mode mode; struct drm_display_mode adjusted_mode; } ;
struct nv50_head_atom {TYPE_7__ set; TYPE_6__ view; TYPE_2__ state; } ;
struct TYPE_11__ {scalar_t__ mode; int hborder; int vborder; } ;
struct TYPE_12__ {int mode; TYPE_4__ underscan; int /*<<< orphan*/  full; } ;
struct TYPE_8__ {struct drm_connector* connector; } ;
struct nouveau_conn_atom {TYPE_5__ scaler; TYPE_1__ state; } ;
struct edid {int dummy; } ;
struct drm_connector {TYPE_3__* edid_blob_ptr; } ;
struct TYPE_10__ {scalar_t__ data; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_3D_FRAME_PACKING ; 
 int DRM_MODE_FLAG_3D_MASK ; 
#define  DRM_MODE_SCALE_ASPECT 129 
#define  DRM_MODE_SCALE_CENTER 128 
 int DRM_MODE_SCALE_FULLSCREEN ; 
 int DRM_MODE_SCALE_NONE ; 
 scalar_t__ UNDERSCAN_AUTO ; 
 scalar_t__ UNDERSCAN_ON ; 
 scalar_t__ drm_detect_hdmi_monitor (struct edid*) ; 
 int /*<<< orphan*/  drm_mode_get_hv_timing (struct drm_display_mode*,int*,int*) ; 
 void* min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nv50_head_atomic_check_view(struct nv50_head_atom *armh,
			    struct nv50_head_atom *asyh,
			    struct nouveau_conn_atom *asyc)
{
	struct drm_connector *connector = asyc->state.connector;
	struct drm_display_mode *omode = &asyh->state.adjusted_mode;
	struct drm_display_mode *umode = &asyh->state.mode;
	int mode = asyc->scaler.mode;
	struct edid *edid;
	int umode_vdisplay, omode_hdisplay, omode_vdisplay;

	if (connector->edid_blob_ptr)
		edid = (struct edid *)connector->edid_blob_ptr->data;
	else
		edid = NULL;

	if (!asyc->scaler.full) {
		if (mode == DRM_MODE_SCALE_NONE)
			omode = umode;
	} else {
		/* Non-EDID LVDS/eDP mode. */
		mode = DRM_MODE_SCALE_FULLSCREEN;
	}

	/* For the user-specified mode, we must ignore doublescan and
	 * the like, but honor frame packing.
	 */
	umode_vdisplay = umode->vdisplay;
	if ((umode->flags & DRM_MODE_FLAG_3D_MASK) == DRM_MODE_FLAG_3D_FRAME_PACKING)
		umode_vdisplay += umode->vtotal;
	asyh->view.iW = umode->hdisplay;
	asyh->view.iH = umode_vdisplay;
	/* For the output mode, we can just use the stock helper. */
	drm_mode_get_hv_timing(omode, &omode_hdisplay, &omode_vdisplay);
	asyh->view.oW = omode_hdisplay;
	asyh->view.oH = omode_vdisplay;

	/* Add overscan compensation if necessary, will keep the aspect
	 * ratio the same as the backend mode unless overridden by the
	 * user setting both hborder and vborder properties.
	 */
	if ((asyc->scaler.underscan.mode == UNDERSCAN_ON ||
	    (asyc->scaler.underscan.mode == UNDERSCAN_AUTO &&
	     drm_detect_hdmi_monitor(edid)))) {
		u32 bX = asyc->scaler.underscan.hborder;
		u32 bY = asyc->scaler.underscan.vborder;
		u32 r = (asyh->view.oH << 19) / asyh->view.oW;

		if (bX) {
			asyh->view.oW -= (bX * 2);
			if (bY) asyh->view.oH -= (bY * 2);
			else    asyh->view.oH  = ((asyh->view.oW * r) + (r / 2)) >> 19;
		} else {
			asyh->view.oW -= (asyh->view.oW >> 4) + 32;
			if (bY) asyh->view.oH -= (bY * 2);
			else    asyh->view.oH  = ((asyh->view.oW * r) + (r / 2)) >> 19;
		}
	}

	/* Handle CENTER/ASPECT scaling, taking into account the areas
	 * removed already for overscan compensation.
	 */
	switch (mode) {
	case DRM_MODE_SCALE_CENTER:
		asyh->view.oW = min((u16)umode->hdisplay, asyh->view.oW);
		asyh->view.oH = min((u16)umode_vdisplay, asyh->view.oH);
		/* fall-through */
	case DRM_MODE_SCALE_ASPECT:
		if (asyh->view.oH < asyh->view.oW) {
			u32 r = (asyh->view.iW << 19) / asyh->view.iH;
			asyh->view.oW = ((asyh->view.oH * r) + (r / 2)) >> 19;
		} else {
			u32 r = (asyh->view.iH << 19) / asyh->view.iW;
			asyh->view.oH = ((asyh->view.oW * r) + (r / 2)) >> 19;
		}
		break;
	default:
		break;
	}

	asyh->set.view = true;
}